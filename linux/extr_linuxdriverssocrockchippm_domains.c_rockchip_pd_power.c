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
struct rockchip_pmu {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct rockchip_pm_domain {int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; struct rockchip_pmu* pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_do_pmu_set_power_domain (struct rockchip_pm_domain*,int) ; 
 int rockchip_pmu_domain_is_on (struct rockchip_pm_domain*) ; 
 int /*<<< orphan*/  rockchip_pmu_restore_qos (struct rockchip_pm_domain*) ; 
 int /*<<< orphan*/  rockchip_pmu_save_qos (struct rockchip_pm_domain*) ; 
 int /*<<< orphan*/  rockchip_pmu_set_idle_request (struct rockchip_pm_domain*,int) ; 

__attribute__((used)) static int rockchip_pd_power(struct rockchip_pm_domain *pd, bool power_on)
{
	struct rockchip_pmu *pmu = pd->pmu;
	int ret;

	mutex_lock(&pmu->mutex);

	if (rockchip_pmu_domain_is_on(pd) != power_on) {
		ret = clk_bulk_enable(pd->num_clks, pd->clks);
		if (ret < 0) {
			dev_err(pmu->dev, "failed to enable clocks\n");
			mutex_unlock(&pmu->mutex);
			return ret;
		}

		if (!power_on) {
			rockchip_pmu_save_qos(pd);

			/* if powering down, idle request to NIU first */
			rockchip_pmu_set_idle_request(pd, true);
		}

		rockchip_do_pmu_set_power_domain(pd, power_on);

		if (power_on) {
			/* if powering up, leave idle mode */
			rockchip_pmu_set_idle_request(pd, false);

			rockchip_pmu_restore_qos(pd);
		}

		clk_bulk_disable(pd->num_clks, pd->clks);
	}

	mutex_unlock(&pmu->mutex);
	return 0;
}