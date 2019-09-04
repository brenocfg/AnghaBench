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
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* baudrate_table ; 

__attribute__((used)) static int f81534_find_clk(u32 baudrate)
{
	int idx;

	for (idx = 0; idx < ARRAY_SIZE(baudrate_table); ++idx) {
		if (baudrate <= baudrate_table[idx] &&
				baudrate_table[idx] % baudrate == 0)
			return idx;
	}

	return -EINVAL;
}