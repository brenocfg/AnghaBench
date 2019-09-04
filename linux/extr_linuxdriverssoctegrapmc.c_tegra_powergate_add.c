#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  power_on; int /*<<< orphan*/  power_off; } ;
struct tegra_powergate {int id; size_t num_clks; struct tegra_powergate* clks; int /*<<< orphan*/  reset; TYPE_1__ genpd; struct tegra_pmc* pmc; } ;
struct tegra_pmc {int /*<<< orphan*/  powergates_available; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM_GENERIC_DOMAINS ; 
 int /*<<< orphan*/  CONFIG_USB_XHCI_TEGRA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int TEGRA_POWERGATE_XUSBA ; 
 int TEGRA_POWERGATE_XUSBC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (struct tegra_powergate) ; 
 int /*<<< orphan*/  kfree (struct tegra_powergate*) ; 
 struct tegra_powergate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_genpd_add_provider_simple (struct device_node*,TYPE_1__*) ; 
 int pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_genpd_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_genpd_power_off ; 
 int /*<<< orphan*/  tegra_genpd_power_on ; 
 int /*<<< orphan*/  tegra_powergate_is_powered (int) ; 
 int tegra_powergate_lookup (struct tegra_pmc*,int /*<<< orphan*/ ) ; 
 int tegra_powergate_of_get_clks (struct tegra_powergate*,struct device_node*) ; 
 int tegra_powergate_of_get_resets (struct tegra_powergate*,struct device_node*,int) ; 
 int /*<<< orphan*/  tegra_powergate_power_up (struct tegra_powergate*,int) ; 

__attribute__((used)) static void tegra_powergate_add(struct tegra_pmc *pmc, struct device_node *np)
{
	struct tegra_powergate *pg;
	int id, err;
	bool off;

	pg = kzalloc(sizeof(*pg), GFP_KERNEL);
	if (!pg)
		return;

	id = tegra_powergate_lookup(pmc, np->name);
	if (id < 0) {
		pr_err("powergate lookup failed for %s: %d\n", np->name, id);
		goto free_mem;
	}

	/*
	 * Clear the bit for this powergate so it cannot be managed
	 * directly via the legacy APIs for controlling powergates.
	 */
	clear_bit(id, pmc->powergates_available);

	pg->id = id;
	pg->genpd.name = np->name;
	pg->genpd.power_off = tegra_genpd_power_off;
	pg->genpd.power_on = tegra_genpd_power_on;
	pg->pmc = pmc;

	off = !tegra_powergate_is_powered(pg->id);

	err = tegra_powergate_of_get_clks(pg, np);
	if (err < 0) {
		pr_err("failed to get clocks for %s: %d\n", np->name, err);
		goto set_available;
	}

	err = tegra_powergate_of_get_resets(pg, np, off);
	if (err < 0) {
		pr_err("failed to get resets for %s: %d\n", np->name, err);
		goto remove_clks;
	}

	if (!IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) {
		if (off)
			WARN_ON(tegra_powergate_power_up(pg, true));

		goto remove_resets;
	}

	/*
	 * FIXME: If XHCI is enabled for Tegra, then power-up the XUSB
	 * host and super-speed partitions. Once the XHCI driver
	 * manages the partitions itself this code can be removed. Note
	 * that we don't register these partitions with the genpd core
	 * to avoid it from powering down the partitions as they appear
	 * to be unused.
	 */
	if (IS_ENABLED(CONFIG_USB_XHCI_TEGRA) &&
	    (id == TEGRA_POWERGATE_XUSBA || id == TEGRA_POWERGATE_XUSBC)) {
		if (off)
			WARN_ON(tegra_powergate_power_up(pg, true));

		goto remove_resets;
	}

	err = pm_genpd_init(&pg->genpd, NULL, off);
	if (err < 0) {
		pr_err("failed to initialise PM domain %s: %d\n", np->name,
		       err);
		goto remove_resets;
	}

	err = of_genpd_add_provider_simple(np, &pg->genpd);
	if (err < 0) {
		pr_err("failed to add PM domain provider for %s: %d\n",
		       np->name, err);
		goto remove_genpd;
	}

	pr_debug("added PM domain %s\n", pg->genpd.name);

	return;

remove_genpd:
	pm_genpd_remove(&pg->genpd);

remove_resets:
	reset_control_put(pg->reset);

remove_clks:
	while (pg->num_clks--)
		clk_put(pg->clks[pg->num_clks]);

	kfree(pg->clks);

set_available:
	set_bit(id, pmc->powergates_available);

free_mem:
	kfree(pg);
}