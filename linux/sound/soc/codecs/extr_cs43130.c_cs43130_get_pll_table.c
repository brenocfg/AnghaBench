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
struct cs43130_pll_params {unsigned int pll_in; unsigned int pll_out; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cs43130_pll_params const*) ; 
 struct cs43130_pll_params const* pll_ratio_table ; 

__attribute__((used)) static const struct cs43130_pll_params *cs43130_get_pll_table(
		unsigned int freq_in, unsigned int freq_out)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pll_ratio_table); i++) {
		if (pll_ratio_table[i].pll_in == freq_in &&
		    pll_ratio_table[i].pll_out == freq_out)
			return &pll_ratio_table[i];
	}

	return NULL;
}