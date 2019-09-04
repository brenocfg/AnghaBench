#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_camera_i2c_reg_array {int member_0; int member_1; int /*<<< orphan*/  member_2; } ;
struct TYPE_4__ {double digital_gain; } ;
typedef  TYPE_1__ CameraState ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (struct msm_camera_i2c_reg_array*) ; 
 int /*<<< orphan*/  LOGE (char*,int) ; 
 int /*<<< orphan*/  MSM_CAMERA_I2C_BYTE_DATA ; 
 int sensor_write_regs (TYPE_1__*,struct msm_camera_i2c_reg_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx179_s5k3p8sp_apply_exposure(CameraState *s, int gain, int integ_lines, int frame_length) {
  //printf("front camera: %d %d %d\n", gain, integ_lines, frame_length);
  int err;

  if (gain > 448) {
    s->digital_gain = (512.0/(512-(gain))) / 8.0;
  } else {
    s->digital_gain = 1.0;
  }

  struct msm_camera_i2c_reg_array reg_array[] = {
    {0x104,0x1,0},

    // FRM_LENGTH
    {0x340, frame_length >> 8, 0}, {0x341, frame_length & 0xff, 0},
    // coarse_int_time
    {0x202, integ_lines >> 8, 0}, {0x203, integ_lines & 0xff,0},
    // global_gain
    {0x204, gain >> 8, 0}, {0x205, gain & 0xff,0},

    {0x104,0x0,0},
  };
  err = sensor_write_regs(s, reg_array, ARRAYSIZE(reg_array), MSM_CAMERA_I2C_BYTE_DATA);
  if (err != 0) {
    LOGE("apply_exposure err %d", err);
  }
  return err;
}