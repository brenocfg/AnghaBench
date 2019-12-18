#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_camera_i2c_reg_array {int member_0; int member_1; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  CameraState ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (struct msm_camera_i2c_reg_array*) ; 
 int /*<<< orphan*/  LOGE (char*,int) ; 
 int /*<<< orphan*/  MSM_CAMERA_I2C_BYTE_DATA ; 
 int ov8865_get_coarse_gain (int) ; 
 int sensor_write_regs (int /*<<< orphan*/ *,struct msm_camera_i2c_reg_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov8865_apply_exposure(CameraState *s, int gain, int integ_lines, int frame_length) {
  //printf("front camera: %d %d %d\n", gain, integ_lines, frame_length);
  int err, gain_bitmap;
  gain_bitmap = (1 << ov8865_get_coarse_gain(gain)) - 1;
  integ_lines *= 16; // The exposure value in reg is in 16ths of a line
  struct msm_camera_i2c_reg_array reg_array[] = {
    //{0x104,0x1,0},

    // FRM_LENGTH
    {0x380e, frame_length >> 8, 0}, {0x380f, frame_length & 0xff, 0},
    // AEC EXPO
    {0x3500, integ_lines >> 16, 0}, {0x3501, integ_lines >> 8, 0}, {0x3502, integ_lines & 0xff,0},
    // AEC MANUAL
    {0x3503, 0x4, 0},
    // AEC GAIN
    {0x3508, gain_bitmap, 0}, {0x3509, 0xf8, 0},

    //{0x104,0x0,0},
  };
  err = sensor_write_regs(s, reg_array, ARRAYSIZE(reg_array), MSM_CAMERA_I2C_BYTE_DATA);
  if (err != 0) {
    LOGE("apply_exposure err %d", err);
  }
  return err;
}