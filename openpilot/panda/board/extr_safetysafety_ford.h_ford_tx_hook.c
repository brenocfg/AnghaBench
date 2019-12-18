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
 scalar_t__ controls_allowed ; 
 scalar_t__ ford_brake_prev ; 
 scalar_t__ ford_gas_prev ; 
 scalar_t__ ford_moving ; 

__attribute__((used)) static int ford_tx_hook(CAN_FIFOMailBox_TypeDef *to_send) {

  int tx = 1;
  // disallow actuator commands if gas or brake (with vehicle moving) are pressed
  // and the the latching controls_allowed flag is True
  int pedal_pressed = ford_gas_prev || (ford_brake_prev && ford_moving);
  bool current_controls_allowed = controls_allowed && !(pedal_pressed);
  int addr = GET_ADDR(to_send);

  // STEER: safety check
  if (addr == 0x3CA) {
    if (!current_controls_allowed) {
      // bits 7-4 need to be 0xF to disallow lkas commands
      if ((GET_BYTE(to_send, 0) & 0xF0) != 0xF0) {
        tx = 0;
      }
    }
  }

  // FORCE CANCEL: safety check only relevant when spamming the cancel button
  // ensuring that set and resume aren't sent
  if (addr == 0x83) {
    if ((GET_BYTE(to_send, 3) & 0x30) != 0) {
      tx = 0;
    }
  }

  // 1 allows the message through
  return tx;
}