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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ int_to_s6 (int) ; 
 int s6_to_int (int) ; 

__attribute__((used)) static u32
calc_bw40_power_rate(u32 value, int delta)
{
	u32 ret = 0;
	int i, tmp;

	for (i = 0; i < 4; i++) {
		tmp = s6_to_int((value >> i*8) & 0xff) + delta;
		ret |= (u32)(int_to_s6(tmp)) << i*8;
	}

	return ret;
}