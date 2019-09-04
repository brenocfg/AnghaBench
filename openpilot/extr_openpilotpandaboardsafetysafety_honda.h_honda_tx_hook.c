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
struct TYPE_3__ {int RIR; int RDLR; int RDTR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 scalar_t__ bosch_hardware ; 
 scalar_t__ brake_prev ; 
 scalar_t__ controls_allowed ; 
 scalar_t__ ego_speed ; 
 scalar_t__ gas_interceptor_prev ; 
 scalar_t__ gas_interceptor_threshold ; 
 scalar_t__ gas_prev ; 

__attribute__((used)) static int honda_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // disallow actuator commands if gas or brake (with vehicle moving) are pressed
  // and the the latching controls_allowed flag is True
  int pedal_pressed = gas_prev || (gas_interceptor_prev > gas_interceptor_threshold) ||
                      (brake_prev && ego_speed);
  int current_controls_allowed = controls_allowed && !(pedal_pressed);

  // BRAKE: safety check
  if ((to_send->RIR>>21) == 0x1FA) {
    if (current_controls_allowed) {
      if ((to_send->RDLR & 0xFFFFFF3F) != to_send->RDLR) return 0;
    } else {
      if ((to_send->RDLR & 0xFFFF0000) != to_send->RDLR) return 0;
    }
  }

  // STEER: safety check
  if ((to_send->RIR>>21) == 0xE4 || (to_send->RIR>>21) == 0x194) {
    if (current_controls_allowed) {
      // all messages are fine here
    } else {
      if ((to_send->RDLR & 0xFFFF0000) != to_send->RDLR) return 0;
    }
  }

  // GAS: safety check
  if ((to_send->RIR>>21) == 0x200) {
    if (current_controls_allowed) {
      // all messages are fine here
    } else {
      if ((to_send->RDLR & 0xFFFF0000) != to_send->RDLR) return 0;
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button in Bosch HW
  // ensuring that only the cancel button press is sent (VAL 2) when controls are off.
  // This avoids unintended engagements while still allowing resume spam
  if (((to_send->RIR>>21) == 0x296) && bosch_hardware &&
      !current_controls_allowed && ((to_send->RDTR >> 4) & 0xFF) == 0) {
    if (((to_send->RDLR >> 5) & 0x7) != 2) return 0;
  }

  // 1 allows the message through
  return true;
}