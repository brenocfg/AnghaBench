#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int min; int max; } ;
typedef  int /*<<< orphan*/  CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int CAN_TO_DEG ; 
 int GET_ADDR (int /*<<< orphan*/ *) ; 
 int GET_BUS (int /*<<< orphan*/ *) ; 
 int GET_BYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LOOKUP_ANGLE_RATE_DOWN ; 
 int /*<<< orphan*/  LOOKUP_ANGLE_RATE_UP ; 
 int angle_control ; 
 TYPE_1__ angle_meas ; 
 scalar_t__ controls_allowed ; 
 int desired_angle_last ; 
 int interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speed ; 
 int to_signed (int,int) ; 
 int toyota_tx_hook (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int toyota_ipas_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  int tx = 1;
  int bypass_standard_tx_hook = 0;
  int bus = GET_BUS(to_send);
  int addr = GET_ADDR(to_send);

  // Check if msg is sent on BUS 0
  if (bus == 0) {

    // STEER ANGLE
    if ((addr == 0x266) || (addr == 0x167)) {

      angle_control = 1;   // we are in angle control mode
      int desired_angle = ((GET_BYTE(to_send, 0) & 0xF) << 8) | GET_BYTE(to_send, 1);
      int ipas_state_cmd = GET_BYTE(to_send, 0) >> 4;
      bool violation = 0;

      desired_angle = to_signed(desired_angle, 12);

      if (controls_allowed) {
        // add 1 to not false trigger the violation
        float delta_angle_float;
        delta_angle_float = (interpolate(LOOKUP_ANGLE_RATE_UP, speed) * CAN_TO_DEG) + 1.;
        int delta_angle_up = (int) (delta_angle_float);
        delta_angle_float = (interpolate(LOOKUP_ANGLE_RATE_DOWN, speed) * CAN_TO_DEG) + 1.;
        int delta_angle_down = (int) (delta_angle_float);

        int highest_desired_angle = desired_angle_last + ((desired_angle_last > 0) ? delta_angle_up : delta_angle_down);
        int lowest_desired_angle = desired_angle_last - ((desired_angle_last > 0) ? delta_angle_down : delta_angle_up);
        if ((desired_angle > highest_desired_angle) ||
            (desired_angle < lowest_desired_angle)){
          violation = 1;
          controls_allowed = 0;
        }
      }

      // desired steer angle should be the same as steer angle measured when controls are off
      if ((!controls_allowed) &&
           ((desired_angle < (angle_meas.min - 1)) ||
            (desired_angle > (angle_meas.max + 1)) ||
            (ipas_state_cmd != 1))) {
        violation = 1;
      }

      desired_angle_last = desired_angle;

      if (violation) {
        tx = 0;
      }
      bypass_standard_tx_hook = 1;
    }
  }

  // check standard toyota stuff as well if addr isn't IPAS related
  if (!bypass_standard_tx_hook) {
    tx &= toyota_tx_hook(to_send);
  }

  return tx;
}