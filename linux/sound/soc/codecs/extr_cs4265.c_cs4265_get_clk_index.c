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
struct TYPE_3__ {int rate; int mclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* clk_map_table ; 

__attribute__((used)) static int cs4265_get_clk_index(int mclk, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(clk_map_table); i++) {
		if (clk_map_table[i].rate == rate &&
				clk_map_table[i].mclk == mclk)
			return i;
	}
	return -EINVAL;
}