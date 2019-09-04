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
typedef  int uint32_t ;

/* Variables and functions */

int cadillac_get_torque_idx(uint32_t addr) {
  if (addr==0x151) return 0;
  else if (addr==0x152) return 1;
  else if (addr==0x153) return 2;
  else return 3;
}