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
struct generic_pm_domain {int dummy; } ;
struct tegra_powergate {scalar_t__ id; struct generic_pm_domain genpd; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct genpd_onecell_data {unsigned int num_domains; int /*<<< orphan*/ * domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct generic_pm_domain* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct tegra_powergate* to_tegra_powergate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct generic_pm_domain *
tegra_powergate_xlate(struct of_phandle_args *spec, void *data)
{
	struct generic_pm_domain *domain = ERR_PTR(-ENOENT);
	struct genpd_onecell_data *genpd = data;
	unsigned int i;

	for (i = 0; i < genpd->num_domains; i++) {
		struct tegra_powergate *powergate;

		powergate = to_tegra_powergate(genpd->domains[i]);
		if (powergate->id == spec->args[0]) {
			domain = &powergate->genpd;
			break;
		}
	}

	return domain;
}