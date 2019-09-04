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
struct skl_clk_rate_cfg_table {unsigned long rate; } ;

/* Variables and functions */
 int SKL_MAX_CLK_RATES ; 

__attribute__((used)) static struct skl_clk_rate_cfg_table *skl_get_rate_cfg(
		struct skl_clk_rate_cfg_table *rcfg,
				unsigned long rate)
{
	int i;

	for (i = 0; (i < SKL_MAX_CLK_RATES) && rcfg[i].rate; i++) {
		if (rcfg[i].rate == rate)
			return &rcfg[i];
	}

	return NULL;
}