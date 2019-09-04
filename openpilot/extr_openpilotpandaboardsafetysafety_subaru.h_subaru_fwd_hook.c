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
typedef  int int32_t ;
struct TYPE_3__ {int RIR; } ;
typedef  TYPE_1__ CAN_FIFOMailBox_TypeDef ;

/* Variables and functions */

__attribute__((used)) static int subaru_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  // shifts bits 29 > 11
  int32_t addr = to_fwd->RIR >> 21;

  // forward CAN 0 > 1
  if (bus_num == 0) {

    return 2; // ES CAN
  }
  // forward CAN 1 > 0, except ES_LKAS
  else if (bus_num == 2) {

    // outback 2015
    if (addr == 0x164) {
      return -1;
    }
    // global platform
    if (addr == 0x122) {
      return -1;
    }
    // ES Distance
    if (addr == 545) {
      return -1;
    }

    return 0; // Main CAN
  }

  // fallback to do not forward
  return -1;
}