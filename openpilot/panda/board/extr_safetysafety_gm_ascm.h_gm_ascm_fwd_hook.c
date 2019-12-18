#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (TYPE_1__*) ; 
 int GET_BYTE (TYPE_1__*,int) ; 

__attribute__((used)) static int gm_ascm_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;

  if (bus_num == 0) {
    int addr = GET_ADDR(to_fwd);
    bus_fwd = 2;
    // do not propagate lkas messages from ascm to actuators, unless supercruise is on
    // block 0x152 and 0x154, which are the lkas command from ASCM1 and ASCM2
    // block 0x315 and 0x2cb, which are the brake and accel commands from ASCM1
    //if ((addr == 0x152) || (addr == 0x154) || (addr == 0x315) || (addr == 0x2cb)) {
    if ((addr == 0x152) || (addr == 0x154)) {
      bool supercruise_on = (GET_BYTE(to_fwd, 4) & 0x10) != 0;  // bit 36
      if (!supercruise_on) {
        bus_fwd = -1;
      }
    }
    if ((addr == 0x151) || (addr == 0x153) || (addr == 0x314)) {
      // on the chassis bus, the OBDII port is on the module side, so we need to read
      // the lkas messages sent by openpilot (put on unused 0x151 ane 0x153 addrs) and send it to
      // the actuator as 0x152 and 0x154
      uint32_t fwd_addr = addr + 1;
      to_fwd->RIR = (fwd_addr << 21) | (to_fwd->RIR & 0x1fffff);
    }
  }

  if (bus_num == 2) {
    bus_fwd = 0;
  }

  return bus_fwd;
}