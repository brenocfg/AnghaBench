#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct msm_camera_i2c_reg_setting* setting; } ;
struct sensorb_cfg_data {TYPE_1__ cfg; int /*<<< orphan*/  cfgtype; int /*<<< orphan*/  member_0; } ;
struct msm_camera_i2c_reg_setting {size_t size; int data_type; int /*<<< orphan*/  delay; int /*<<< orphan*/  addr_type; struct msm_camera_i2c_reg_array* reg_setting; } ;
struct msm_camera_i2c_reg_array {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sensor_fd; } ;
typedef  TYPE_2__ CameraState ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_WRITE_I2C_ARRAY ; 
 int /*<<< orphan*/  MSM_CAMERA_I2C_WORD_ADDR ; 
 int /*<<< orphan*/  VIDIOC_MSM_SENSOR_CFG ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sensorb_cfg_data*) ; 

int sensor_write_regs(CameraState *s, struct msm_camera_i2c_reg_array* arr, size_t size, int data_type) {
  struct msm_camera_i2c_reg_setting out_settings = {
    .reg_setting = arr,
    .size = size,
    .addr_type = MSM_CAMERA_I2C_WORD_ADDR,
    .data_type = data_type,
    .delay = 0,
  };
  struct sensorb_cfg_data cfg_data = {0};
  cfg_data.cfgtype = CFG_WRITE_I2C_ARRAY;
  cfg_data.cfg.setting = &out_settings;
  return ioctl(s->sensor_fd, VIDIOC_MSM_SENSOR_CFG, &cfg_data);
}