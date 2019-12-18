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
typedef  scalar_t__ u_int ;
struct TYPE_3__ {int rate; scalar_t__ mclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ abs (scalar_t__) ; 
 TYPE_1__* clk_map_table ; 

__attribute__((used)) static int cs42l52_get_clk(int mclk, int rate)
{
	int i, ret = -EINVAL;
	u_int mclk1, mclk2 = 0;

	for (i = 0; i < ARRAY_SIZE(clk_map_table); i++) {
		if (clk_map_table[i].rate == rate) {
			mclk1 = clk_map_table[i].mclk;
			if (abs(mclk - mclk1) < abs(mclk - mclk2)) {
				mclk2 = mclk1;
				ret = i;
			}
		}
	}
	return ret;
}