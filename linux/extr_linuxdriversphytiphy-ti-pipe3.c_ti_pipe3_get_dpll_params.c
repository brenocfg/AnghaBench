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
struct ti_pipe3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  sys_clk; struct pipe3_dpll_map* dpll_map; } ;
struct pipe3_dpll_params {int dummy; } ;
struct pipe3_dpll_map {long rate; struct pipe3_dpll_params params; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static struct pipe3_dpll_params *ti_pipe3_get_dpll_params(struct ti_pipe3 *phy)
{
	unsigned long rate;
	struct pipe3_dpll_map *dpll_map = phy->dpll_map;

	rate = clk_get_rate(phy->sys_clk);

	for (; dpll_map->rate; dpll_map++) {
		if (rate == dpll_map->rate)
			return &dpll_map->params;
	}

	dev_err(phy->dev, "No DPLL configuration for %lu Hz SYS CLK\n", rate);

	return NULL;
}