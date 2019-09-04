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
struct cs43130_clk_gen {int mclk_int; int fs; } ;

/* Variables and functions */

__attribute__((used)) static const struct cs43130_clk_gen *cs43130_get_clk_gen(int mclk_int, int fs,
		const struct cs43130_clk_gen *clk_gen_table, int len_clk_gen_table)
{
	int i;

	for (i = 0; i < len_clk_gen_table; i++) {
		if (clk_gen_table[i].mclk_int == mclk_int &&
		    clk_gen_table[i].fs == fs)
			return &clk_gen_table[i];
	}

	return NULL;
}