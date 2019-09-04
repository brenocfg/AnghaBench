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
typedef  int uint32_t ;
struct TYPE_3__ {int RDTR; int RIR; int RDHR; int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int chrysler_camera_detected ; 
 int chrysler_cruise_engaged_last ; 
 int /*<<< orphan*/  chrysler_torque_meas ; 
 int controls_allowed ; 
 int /*<<< orphan*/  update_sample (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void chrysler_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {
  int bus = (to_push->RDTR >> 4) & 0xFF;
  uint32_t addr;
  if (to_push->RIR & 4) {
    // Extended
    // Not looked at, but have to be separated
    // to avoid address collision
    addr = to_push->RIR >> 3;
  } else {
    // Normal
    addr = to_push->RIR >> 21;
  }

  // Measured eps torque
  if (addr == 544) {
    int rdhr = to_push->RDHR;
    int torque_meas_new = ((rdhr & 0x7) << 8) + ((rdhr & 0xFF00) >> 8) - 1024;

    // update array of samples
    update_sample(&chrysler_torque_meas, torque_meas_new);
  }

  // enter controls on rising edge of ACC, exit controls on ACC off
  if (addr == 0x1f4) {
    int cruise_engaged = ((to_push->RDLR & 0x380000) >> 19) == 7;
    if (cruise_engaged && !chrysler_cruise_engaged_last) {
      controls_allowed = 1;
    } else if (!cruise_engaged) {
      controls_allowed = 0;
    }
    chrysler_cruise_engaged_last = cruise_engaged;
  }

  // check if stock camera ECU is still online
  if (bus == 0 && addr == 0x292) {
    chrysler_camera_detected = 1;
    controls_allowed = 0;
  }
}