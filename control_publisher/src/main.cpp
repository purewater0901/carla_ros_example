#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <memory>
#include <carla_msgs/CarlaEgoVehicleControl.h>
#include <carla_msgs/CarlaEgoVehicleStatus.h>
#include <tf2/convert.h>
#include <tf/transform_broadcaster.h>

void callback(const carla_msgs::CarlaEgoVehicleStatus& msg)
{
    double acceleration_x = msg.acceleration.linear.x;
    double acceleration_y = msg.acceleration.linear.y;
    double velocity_x = msg.velocity;

    ROS_INFO("x acceleration %f", acceleration_x);
    ROS_INFO("y acceleration %f", acceleration_y);
    ROS_INFO("velocity %f", velocity_x);
}

void callbackPosition(const nav_msgs::Odometry& msgs)
{
    double position_x = msgs.pose.pose.position.x;
    double position_y = msgs.pose.pose.position.y;
    double position_z = msgs.pose.pose.position.z;
    double yaw = tf::getYaw(msgs.pose.pose.orientation);

    ROS_INFO("Position x %f", position_x);
    ROS_INFO("Position y %f", position_y);
    ROS_INFO("Position z %f", position_z);
    ROS_INFO("Position yaw %f", yaw);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "controller");
    ros::NodeHandle nh;

    //ros::Publisher control_pub = nh.advertise<carla_msgs::CarlaEgoVehicleControl>("/carla/hero/vehicle_control_cmd", 10);
    ros::Subscriber status_sub = nh.subscribe("/carla/hero/vehicle_status", 1, callback);
    ros::Subscriber position_sub = nh.subscribe("/carla/hero/odometry", 1, callbackPosition);
    //ros::Rate loop_rate(100);

   /*
    while(ros::ok())
    {
        carla_msgs::CarlaEgoVehicleControl command;
        command.throttle = 0.5;

        control_pub.publish(command);

        ros::spinOnce();
        loop_rate.sleep();
    }
    */

   ros::spin();

    return 0;
}

