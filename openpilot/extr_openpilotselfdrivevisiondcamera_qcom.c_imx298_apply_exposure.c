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
 int min (int,int) ; 
 int sensor_write_regs (TYPE_1__*,struct msm_camera_i2c_reg_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx298_apply_exposure(CameraState *s, int gain, int integ_lines, int frame_length) {
  int err;

  int analog_gain = min(gain, 448);

  if (gain > 448) {
    s->digital_gain = (512.0/(512-(gain))) / 8.0;
  } else {
    s->digital_gain = 1.0;
  }

  //printf("%5d/%5d %5d %f\n", s->cur_integ_lines, s->cur_frame_length, analog_gain, s->digital_gain);

  int digital_gain = 0x100;

  float white_balance[] = {0.4609375, 1.0, 0.546875};
  //float white_balance[] = {1.0, 1.0, 1.0};

  int digital_gain_gr = digital_gain / white_balance[1];
  int digital_gain_gb = digital_gain / white_balance[1];
  int digital_gain_r = digital_gain / white_balance[0];
  int digital_gain_b = digital_gain / white_balance[2];

  struct msm_camera_i2c_reg_array reg_array[] = {
    // REG_HOLD
    {0x104,0x1,0},
    {0x3002,0x0,0}, // long autoexposure off

    // FRM_LENGTH
    {0x340, frame_length >> 8, 0}, {0x341, frame_length & 0xff, 0},
    // INTEG_TIME aka coarse_int_time_addr aka shutter speed
    {0x202, integ_lines >> 8, 0}, {0x203, integ_lines & 0xff,0},
    // global_gain_addr
    // if you assume 1x gain is 32, 448 is 14x gain, aka 2^14=16384
    {0x204, analog_gain >> 8, 0}, {0x205, analog_gain & 0xff,0},

    // digital gain for colors: gain_greenR, gain_red, gain_blue, gain_greenB
    /*{0x20e, digital_gain_gr >> 8, 0}, {0x20f,digital_gain_gr & 0xFF,0},
    {0x210, digital_gain_r >> 8, 0}, {0x211,digital_gain_r & 0xFF,0},
    {0x212, digital_gain_b >> 8, 0}, {0x213,digital_gain_b & 0xFF,0},
    {0x214, digital_gain_gb >> 8, 0}, {0x215,digital_gain_gb & 0xFF,0},*/

    // REG_HOLD
    {0x104,0x0,0},
  };

  err = sensor_write_regs(s, reg_array, ARRAYSIZE(reg_array), MSM_CAMERA_I2C_BYTE_DATA);
  if (err != 0) {
    LOGE("apply_exposure err %d", err);
  }
  return err;
}