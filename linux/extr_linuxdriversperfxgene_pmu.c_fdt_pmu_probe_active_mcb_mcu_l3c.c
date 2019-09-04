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
struct xgene_pmu {int l3c_active_mask; int mcb_active_mask; int mc_active_mask; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSW_CSWCR ; 
 unsigned int CSW_CSWCR_DUALMCB_MASK ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  MCBADDRMR ; 
 unsigned int MCBADDRMR_DUALMCU_MODE_MASK ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int fdt_pmu_probe_active_mcb_mcu_l3c(struct xgene_pmu *xgene_pmu,
					    struct platform_device *pdev)
{
	struct regmap *csw_map, *mcba_map, *mcbb_map;
	struct device_node *np = pdev->dev.of_node;
	unsigned int reg;

	csw_map = syscon_regmap_lookup_by_phandle(np, "regmap-csw");
	if (IS_ERR(csw_map)) {
		dev_err(&pdev->dev, "unable to get syscon regmap csw\n");
		return PTR_ERR(csw_map);
	}

	mcba_map = syscon_regmap_lookup_by_phandle(np, "regmap-mcba");
	if (IS_ERR(mcba_map)) {
		dev_err(&pdev->dev, "unable to get syscon regmap mcba\n");
		return PTR_ERR(mcba_map);
	}

	mcbb_map = syscon_regmap_lookup_by_phandle(np, "regmap-mcbb");
	if (IS_ERR(mcbb_map)) {
		dev_err(&pdev->dev, "unable to get syscon regmap mcbb\n");
		return PTR_ERR(mcbb_map);
	}

	xgene_pmu->l3c_active_mask = 0x1;
	if (regmap_read(csw_map, CSW_CSWCR, &reg))
		return -EINVAL;

	if (reg & CSW_CSWCR_DUALMCB_MASK) {
		/* Dual MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Probe all active MC(s) */
		if (regmap_read(mcbb_map, MCBADDRMR, &reg))
			return 0;
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0xF : 0x5;
	} else {
		/* Single MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Probe all active MC(s) */
		if (regmap_read(mcba_map, MCBADDRMR, &reg))
			return 0;
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0x3 : 0x1;
	}

	return 0;
}