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
typedef  int u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PMU_TYPE_IOB 132 
#define  PMU_TYPE_IOB_SLOW 131 
#define  PMU_TYPE_L3C 130 
#define  PMU_TYPE_MC 129 
#define  PMU_TYPE_MCB 128 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static char *xgene_pmu_dev_name(struct device *dev, u32 type, int id)
{
	switch (type) {
	case PMU_TYPE_L3C:
		return devm_kasprintf(dev, GFP_KERNEL, "l3c%d", id);
	case PMU_TYPE_IOB:
		return devm_kasprintf(dev, GFP_KERNEL, "iob%d", id);
	case PMU_TYPE_IOB_SLOW:
		return devm_kasprintf(dev, GFP_KERNEL, "iob_slow%d", id);
	case PMU_TYPE_MCB:
		return devm_kasprintf(dev, GFP_KERNEL, "mcb%d", id);
	case PMU_TYPE_MC:
		return devm_kasprintf(dev, GFP_KERNEL, "mc%d", id);
	default:
		return devm_kasprintf(dev, GFP_KERNEL, "unknown");
	}
}