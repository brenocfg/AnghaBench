#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_domains; struct generic_pm_domain** domains; } ;
struct rockchip_pmu {TYPE_1__ genpd_data; } ;
struct rockchip_pm_domain {int dummy; } ;
struct generic_pm_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rockchip_pm_remove_one_domain (struct rockchip_pm_domain*) ; 
 struct rockchip_pm_domain* to_rockchip_pd (struct generic_pm_domain*) ; 

__attribute__((used)) static void rockchip_pm_domain_cleanup(struct rockchip_pmu *pmu)
{
	struct generic_pm_domain *genpd;
	struct rockchip_pm_domain *pd;
	int i;

	for (i = 0; i < pmu->genpd_data.num_domains; i++) {
		genpd = pmu->genpd_data.domains[i];
		if (genpd) {
			pd = to_rockchip_pd(genpd);
			rockchip_pm_remove_one_domain(pd);
		}
	}

	/* devm will free our memory */
}