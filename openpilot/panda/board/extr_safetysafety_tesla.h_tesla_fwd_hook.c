#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int RDLR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */
 int GET_ADDR (TYPE_1__*) ; 
 int GET_BYTE (TYPE_1__*,int) ; 
 int GET_BYTES_04 (TYPE_1__*) ; 

__attribute__((used)) static int tesla_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;
  int addr = GET_ADDR(to_fwd);

  if (bus_num == 0) {
    // change inhibit of GTW_epasControl

    if (addr != 0x214) {
      // remove EPB_epasControl
      bus_fwd = 2; // Custom EPAS bus
    }
    if (addr == 0x101) {
      to_fwd->RDLR = GET_BYTES_04(to_fwd) | 0x4000; // 0x4000: WITH_ANGLE, 0xC000: WITH_BOTH (angle and torque)
      uint32_t checksum = (GET_BYTE(to_fwd, 1) + GET_BYTE(to_fwd, 0) + 2) & 0xFF;
      to_fwd->RDLR = GET_BYTES_04(to_fwd) & 0xFFFF;
      to_fwd->RDLR = GET_BYTES_04(to_fwd) + (checksum << 16);
    }
  }
  if (bus_num == 2) {
    // remove GTW_epasControl in forwards
    if (addr != 0x101) {
      bus_fwd = 0;  // Chassis CAN
    }
  }
  return bus_fwd;
}