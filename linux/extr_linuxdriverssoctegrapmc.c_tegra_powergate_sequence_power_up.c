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
struct tegra_powergate {unsigned int id; int num_clks; int /*<<< orphan*/  pmc; struct reset_control* reset; struct clk** clks; } ;
struct reset_control {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tegra_powergate*) ; 
 struct tegra_powergate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int) ; 
 int /*<<< orphan*/  tegra_powergate_is_available (unsigned int) ; 
 int tegra_powergate_power_up (struct tegra_powergate*,int) ; 

int tegra_powergate_sequence_power_up(unsigned int id, struct clk *clk,
				      struct reset_control *rst)
{
	struct tegra_powergate *pg;
	int err;

	if (!tegra_powergate_is_available(id))
		return -EINVAL;

	pg = kzalloc(sizeof(*pg), GFP_KERNEL);
	if (!pg)
		return -ENOMEM;

	pg->id = id;
	pg->clks = &clk;
	pg->num_clks = 1;
	pg->reset = rst;
	pg->pmc = pmc;

	err = tegra_powergate_power_up(pg, false);
	if (err)
		pr_err("failed to turn on partition %d: %d\n", id, err);

	kfree(pg);

	return err;
}