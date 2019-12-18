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

__attribute__((used)) static int subaru_fwd_hook(int bus_num, CAN_FIFOMailBox_TypeDef *to_fwd) {

  int bus_fwd = -1;
  if (bus_num == 0) {
    bus_fwd = 2;  // Camera CAN
  }
  if (bus_num == 2) {
    // 290 is LKAS for Global Platform
    // 356 is LKAS for outback 2015
    // 545 is ES_Distance
    // 802 is ES_LKAS
    int addr = GET_ADDR(to_fwd);
    int block_msg = (addr == 290) || (addr == 356) || (addr == 545) || (addr == 802);
    if (!block_msg) {
      bus_fwd = 0;  // Main CAN
    }
  }

  // fallback to do not forward
  return bus_fwd;
}