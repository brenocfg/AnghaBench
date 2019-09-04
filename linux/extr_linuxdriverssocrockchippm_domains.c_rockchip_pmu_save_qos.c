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
struct rockchip_pm_domain {int num_qos; int /*<<< orphan*/ ** qos_save_regs; int /*<<< orphan*/ * qos_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  QOS_BANDWIDTH ; 
 int /*<<< orphan*/  QOS_EXTCONTROL ; 
 int /*<<< orphan*/  QOS_MODE ; 
 int /*<<< orphan*/  QOS_PRIORITY ; 
 int /*<<< orphan*/  QOS_SATURATION ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_pmu_save_qos(struct rockchip_pm_domain *pd)
{
	int i;

	for (i = 0; i < pd->num_qos; i++) {
		regmap_read(pd->qos_regmap[i],
			    QOS_PRIORITY,
			    &pd->qos_save_regs[0][i]);
		regmap_read(pd->qos_regmap[i],
			    QOS_MODE,
			    &pd->qos_save_regs[1][i]);
		regmap_read(pd->qos_regmap[i],
			    QOS_BANDWIDTH,
			    &pd->qos_save_regs[2][i]);
		regmap_read(pd->qos_regmap[i],
			    QOS_SATURATION,
			    &pd->qos_save_regs[3][i]);
		regmap_read(pd->qos_regmap[i],
			    QOS_EXTCONTROL,
			    &pd->qos_save_regs[4][i]);
	}
	return 0;
}