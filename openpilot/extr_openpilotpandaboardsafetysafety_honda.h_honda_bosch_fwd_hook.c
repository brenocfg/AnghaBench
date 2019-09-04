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
typedef  int uint8_t ;
struct TYPE_3__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */

__attribute__((used)) static int honda_bosch_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {
  if (bus_num == 1 || bus_num == 2) {
    int addr = to_fwd->RIR>>21;
    return addr != 0xE4 && addr != 0x33D ? (uint8_t)(~bus_num & 0x3) : -1;
  }
  return -1;
}