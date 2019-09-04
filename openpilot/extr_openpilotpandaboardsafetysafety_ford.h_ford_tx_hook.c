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
struct TYPE_3__ {int RIR; int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 scalar_t__ controls_allowed ; 
 scalar_t__ ford_brake_prev ; 
 scalar_t__ ford_gas_prev ; 
 scalar_t__ ford_is_moving ; 

__attribute__((used)) static int ford_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  // disallow actuator commands if gas or brake (with vehicle moving) are pressed
  // and the the latching controls_allowed flag is True
  int pedal_pressed = ford_gas_prev || (ford_brake_prev && ford_is_moving);
  int current_controls_allowed = controls_allowed && !(pedal_pressed);

  // STEER: safety check
  if ((to_send->RIR>>21) == 0x3CA) {
    if (current_controls_allowed) {
      // all messages are fine here
    } else {
      // bits 7-4 need to be 0xF to disallow lkas commands
      if (((to_send->RDLR >> 4) & 0xF) != 0xF) return 0;
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button
  // ensuring that set and resume aren't sent
  if ((to_send->RIR>>21) == 0x83) {
    if ((to_send->RDLR >> 28) & 0x3) return 0;
  }

  // 1 allows the message through
  return true;
}