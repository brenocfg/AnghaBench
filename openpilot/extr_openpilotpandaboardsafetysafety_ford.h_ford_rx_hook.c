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
struct TYPE_3__ {int RIR; int RDLR; int RDHR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int controls_allowed ; 
 int ford_brake_prev ; 
 int ford_gas_prev ; 
 int ford_is_moving ; 

__attribute__((used)) static void ford_rx_hook(CAN_FIFOMailBox_TypeDef *to_push) {

  if ((to_push->RIR>>21) == 0x217) {
    // wheel speeds are 14 bits every 16
    ford_is_moving = 0xFCFF & (to_push->RDLR | (to_push->RDLR >> 16) |
                               to_push->RDHR | (to_push->RDHR >> 16));
  }

  // state machine to enter and exit controls
  if ((to_push->RIR>>21) == 0x83) {
    int cancel = ((to_push->RDLR >> 8) & 0x1);
    int set_or_resume = (to_push->RDLR >> 28) & 0x3;
    if (cancel) {
      controls_allowed = 0;
    } else if (set_or_resume) {
      controls_allowed = 1;
    }
  }

  // exit controls on rising edge of brake press or on brake press when
  // speed > 0
  if ((to_push->RIR>>21) == 0x165) {
    int brake = to_push->RDLR & 0x20;
    if (brake && (!(ford_brake_prev) || ford_is_moving)) {
      controls_allowed = 0;
    }
    ford_brake_prev = brake;
  }

  // exit controls on rising edge of gas press
  if ((to_push->RIR>>21) == 0x204) {
    int gas = to_push->RDLR & 0xFF03;
    if (gas && !(ford_gas_prev)) {
      controls_allowed = 0;
    }
    ford_gas_prev = gas;
  }
}