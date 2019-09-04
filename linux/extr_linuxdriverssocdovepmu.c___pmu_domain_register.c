#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  power_on; int /*<<< orphan*/  power_off; } ;
struct pmu_domain {unsigned int pwr_mask; TYPE_2__ base; TYPE_1__* pmu; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ pmu_base; } ;

/* Variables and functions */
 scalar_t__ PMU_PWR ; 
 int /*<<< orphan*/  of_genpd_add_provider_simple (struct device_node*,TYPE_2__*) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmu_domain_power_off ; 
 int /*<<< orphan*/  pmu_domain_power_on ; 
 unsigned int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void __pmu_domain_register(struct pmu_domain *domain,
	struct device_node *np)
{
	unsigned int val = readl_relaxed(domain->pmu->pmu_base + PMU_PWR);

	domain->base.power_off = pmu_domain_power_off;
	domain->base.power_on = pmu_domain_power_on;

	pm_genpd_init(&domain->base, NULL, !(val & domain->pwr_mask));

	if (np)
		of_genpd_add_provider_simple(np, &domain->base);
}