#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int RIR; int RDHR; int RDLR; int RDTR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int controls_allowed ; 
 int to_signed (int,int) ; 
 int toyota_camera_forwarded ; 
 int toyota_cruise_engaged_last ; 
 int toyota_dbc_eps_torque_factor ; 
 int toyota_giraffe_switch_1 ; 
 int /*<<< orphan*/  toyota_torque_meas ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void toyota_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  // get eps motor torque (0.66 factor in dbc)
  if ((to_push->RIR>>21) == 0x260) {
    int torque_meas_new = (((to_push->RDHR) & 0xFF00) | ((to_push->RDHR >> 16) & 0xFF));
    torque_meas_new = to_signed(torque_meas_new, 16);

    // scale by dbc_factor
    torque_meas_new = (torque_meas_new * toyota_dbc_eps_torque_factor) / 100;

    // increase torque_meas by 1 to be conservative on rounding
    torque_meas_new += (torque_meas_new > 0 ? 1 : -1);

    // update array of sample
    update_sample(&toyota_torque_meas, torque_meas_new);
  }

  // enter controls on rising edge of ACC, exit controls on ACC off
  if ((to_push->RIR>>21) == 0x1D2) {
    // 5th bit is CRUISE_ACTIVE
    int cruise_engaged = to_push->RDLR & 0x20;
    if (cruise_engaged && !toyota_cruise_engaged_last) {
      controls_allowed = 1;
    } else if (!cruise_engaged) {
      controls_allowed = 0;
    }
    toyota_cruise_engaged_last = cruise_engaged;
  }

  int bus = (to_push->RDTR >> 4) & 0xF;
  // msgs are only on bus 2 if panda is connected to frc
  if (bus == 2) {
    toyota_camera_forwarded = 1;
  }

  // 0x2E4 is lkas cmd. If it is on bus 0, then giraffe switch 1 is high
  if ((to_push->RIR>>21) == 0x2E4 && (bus == 0)) {
    toyota_giraffe_switch_1 = 1;
  }
}