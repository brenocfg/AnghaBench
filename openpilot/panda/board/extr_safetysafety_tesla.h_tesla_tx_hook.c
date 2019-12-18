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
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TESLA_LOOKUP_ANGLE_RATE_DOWN ; 
 int /*<<< orphan*/  TESLA_LOOKUP_ANGLE_RATE_UP ; 
 int /*<<< orphan*/  TESLA_LOOKUP_MAX_ANGLE ; 
 scalar_t__ controls_allowed ; 
 int fmax_limit_check (float,float,float) ; 
 int interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tesla_desired_angle_last ; 
 int /*<<< orphan*/  tesla_speed ; 

__attribute__((used)) static int tesla_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  int tx = 1;
  int addr = GET_ADDR(to_send);

  // do not transmit CAN message if steering angle too high
  // DAS_steeringControl::DAS_steeringAngleRequest
  if (addr == 0x488) {
    float angle_raw = ((GET_BYTE(to_send, 0) & 0x7F) << 8) + GET_BYTE(to_send, 1);
    float desired_angle = (angle_raw * 0.1) - 1638.35;
    bool violation = 0;
    int st_enabled = GET_BYTE(to_send, 2) & 0x40;

    if (st_enabled == 0) {
      //steering is not enabled, do not check angles and do send
      tesla_desired_angle_last = desired_angle;
    } else if (controls_allowed) {
      // add 1 to not false trigger the violation
      float delta_angle_up = interpolate(TESLA_LOOKUP_ANGLE_RATE_UP, tesla_speed) + 1.;
      float delta_angle_down = interpolate(TESLA_LOOKUP_ANGLE_RATE_DOWN, tesla_speed) + 1.;
      float highest_desired_angle = tesla_desired_angle_last + ((tesla_desired_angle_last > 0.) ? delta_angle_up : delta_angle_down);
      float lowest_desired_angle = tesla_desired_angle_last - ((tesla_desired_angle_last > 0.) ? delta_angle_down : delta_angle_up);
      float TESLA_MAX_ANGLE = interpolate(TESLA_LOOKUP_MAX_ANGLE, tesla_speed) + 1.;

      //check for max angles
      violation |= fmax_limit_check(desired_angle, TESLA_MAX_ANGLE, -TESLA_MAX_ANGLE);

      //check for angle delta changes
      violation |= fmax_limit_check(desired_angle, highest_desired_angle, lowest_desired_angle);

      if (violation) {
        controls_allowed = 0;
        tx = 0;
      }
      tesla_desired_angle_last = desired_angle;
    } else {
      tx = 0;
    }
  }
  return tx;
}