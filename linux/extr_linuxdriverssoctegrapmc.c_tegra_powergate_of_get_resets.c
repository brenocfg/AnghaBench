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
struct tegra_powergate {int /*<<< orphan*/  reset; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_reset_control_array_get_exclusive (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_powergate_of_get_resets(struct tegra_powergate *pg,
					 struct device_node *np, bool off)
{
	int err;

	pg->reset = of_reset_control_array_get_exclusive(np);
	if (IS_ERR(pg->reset)) {
		err = PTR_ERR(pg->reset);
		pr_err("failed to get device resets: %d\n", err);
		return err;
	}

	if (off)
		err = reset_control_assert(pg->reset);
	else
		err = reset_control_deassert(pg->reset);

	if (err)
		reset_control_put(pg->reset);

	return err;
}