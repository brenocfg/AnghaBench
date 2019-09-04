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
struct TYPE_2__ {int type; int enable_mask; } ;
struct xgene_pmu_dev_ctx {int /*<<< orphan*/  name; struct xgene_pmu_dev* pmu_dev; TYPE_1__ inf; } ;
struct xgene_pmu_dev {int /*<<< orphan*/  attr_groups; TYPE_1__* inf; struct xgene_pmu* parent; } ;
struct xgene_pmu {int l3c_active_mask; int mcb_active_mask; int mc_active_mask; int /*<<< orphan*/  version; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCP_PMU_V3 ; 
#define  PMU_TYPE_IOB 132 
#define  PMU_TYPE_IOB_SLOW 131 
#define  PMU_TYPE_L3C 130 
#define  PMU_TYPE_MC 129 
#define  PMU_TYPE_MCB 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct xgene_pmu_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iob_fast_pmu_v3_attr_groups ; 
 int /*<<< orphan*/  iob_pmu_attr_groups ; 
 int /*<<< orphan*/  iob_slow_pmu_v3_attr_groups ; 
 int /*<<< orphan*/  l3c_pmu_attr_groups ; 
 int /*<<< orphan*/  l3c_pmu_v3_attr_groups ; 
 int /*<<< orphan*/  mc_pmu_attr_groups ; 
 int /*<<< orphan*/  mc_pmu_v3_attr_groups ; 
 int /*<<< orphan*/  mcb_pmu_attr_groups ; 
 int /*<<< orphan*/  mcb_pmu_v3_attr_groups ; 
 scalar_t__ xgene_init_perf (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xgene_pmu_dev_add(struct xgene_pmu *xgene_pmu, struct xgene_pmu_dev_ctx *ctx)
{
	struct device *dev = xgene_pmu->dev;
	struct xgene_pmu_dev *pmu;

	pmu = devm_kzalloc(dev, sizeof(*pmu), GFP_KERNEL);
	if (!pmu)
		return -ENOMEM;
	pmu->parent = xgene_pmu;
	pmu->inf = &ctx->inf;
	ctx->pmu_dev = pmu;

	switch (pmu->inf->type) {
	case PMU_TYPE_L3C:
		if (!(xgene_pmu->l3c_active_mask & pmu->inf->enable_mask))
			return -ENODEV;
		if (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = l3c_pmu_v3_attr_groups;
		else
			pmu->attr_groups = l3c_pmu_attr_groups;
		break;
	case PMU_TYPE_IOB:
		if (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = iob_fast_pmu_v3_attr_groups;
		else
			pmu->attr_groups = iob_pmu_attr_groups;
		break;
	case PMU_TYPE_IOB_SLOW:
		if (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = iob_slow_pmu_v3_attr_groups;
		break;
	case PMU_TYPE_MCB:
		if (!(xgene_pmu->mcb_active_mask & pmu->inf->enable_mask))
			return -ENODEV;
		if (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = mcb_pmu_v3_attr_groups;
		else
			pmu->attr_groups = mcb_pmu_attr_groups;
		break;
	case PMU_TYPE_MC:
		if (!(xgene_pmu->mc_active_mask & pmu->inf->enable_mask))
			return -ENODEV;
		if (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = mc_pmu_v3_attr_groups;
		else
			pmu->attr_groups = mc_pmu_attr_groups;
		break;
	default:
		return -EINVAL;
	}

	if (xgene_init_perf(pmu, ctx->name)) {
		dev_err(dev, "%s PMU: Failed to init perf driver\n", ctx->name);
		return -ENODEV;
	}

	dev_info(dev, "%s PMU registered\n", ctx->name);

	return 0;
}