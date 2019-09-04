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
struct TYPE_3__ {unsigned int sr; unsigned int clk; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* clkref ; 

__attribute__((used)) static unsigned int get_pdm_clk(unsigned int sr)
{
	unsigned int i, count, clk, div;

	clk = 0;
	if (!sr)
		return clk;

	count = ARRAY_SIZE(clkref);
	for (i = 0; i < count; i++) {
		if (sr % clkref[i].sr)
			continue;
		div = sr / clkref[i].sr;
		if ((div & (div - 1)) == 0) {
			clk = clkref[i].clk;
			break;
		}
	}

	return clk;
}