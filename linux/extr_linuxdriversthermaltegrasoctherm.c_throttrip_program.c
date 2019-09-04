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
typedef  scalar_t__ u32 ;
struct tegra_tsensor_group {int /*<<< orphan*/  thermctl_lvl0_dn_thresh_mask; int /*<<< orphan*/  thermctl_lvl0_up_thresh_mask; int /*<<< orphan*/  thermctl_lvl0_offset; } ;
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* soc; } ;
struct soctherm_throt_cfg {unsigned int id; int /*<<< orphan*/  init; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int thresh_grain; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ REG_SET_MASK (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int THERMCTL_LVL0_CPU0_CPU_THROT_HEAVY ; 
 int THERMCTL_LVL0_CPU0_CPU_THROT_LIGHT ; 
 int /*<<< orphan*/  THERMCTL_LVL0_CPU0_CPU_THROT_MASK ; 
 int /*<<< orphan*/  THERMCTL_LVL0_CPU0_EN_MASK ; 
 int THERMCTL_LVL0_CPU0_GPU_THROT_HEAVY ; 
 int THERMCTL_LVL0_CPU0_GPU_THROT_LIGHT ; 
 int /*<<< orphan*/  THERMCTL_LVL0_CPU0_GPU_THROT_MASK ; 
 scalar_t__ THERMCTL_LVL_REG (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int THROTTLE_HEAVY ; 
 unsigned int THROTTLE_LIGHT ; 
 struct tegra_soctherm* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int) ; 
 int enforce_temp_range (struct device*,int) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int throttrip_program(struct device *dev,
			     const struct tegra_tsensor_group *sg,
			     struct soctherm_throt_cfg *stc,
			     int trip_temp)
{
	struct tegra_soctherm *ts = dev_get_drvdata(dev);
	int temp, cpu_throt, gpu_throt;
	unsigned int throt;
	u32 r, reg_off;

	if (!sg || !stc || !stc->init)
		return -EINVAL;

	temp = enforce_temp_range(dev, trip_temp) / ts->soc->thresh_grain;

	/* Hardcode LIGHT on LEVEL1 and HEAVY on LEVEL2 */
	throt = stc->id;
	reg_off = THERMCTL_LVL_REG(sg->thermctl_lvl0_offset, throt + 1);

	if (throt == THROTTLE_LIGHT) {
		cpu_throt = THERMCTL_LVL0_CPU0_CPU_THROT_LIGHT;
		gpu_throt = THERMCTL_LVL0_CPU0_GPU_THROT_LIGHT;
	} else {
		cpu_throt = THERMCTL_LVL0_CPU0_CPU_THROT_HEAVY;
		gpu_throt = THERMCTL_LVL0_CPU0_GPU_THROT_HEAVY;
		if (throt != THROTTLE_HEAVY)
			dev_warn(dev,
				 "invalid throt id %d - assuming HEAVY",
				 throt);
	}

	r = readl(ts->regs + reg_off);
	r = REG_SET_MASK(r, sg->thermctl_lvl0_up_thresh_mask, temp);
	r = REG_SET_MASK(r, sg->thermctl_lvl0_dn_thresh_mask, temp);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_CPU_THROT_MASK, cpu_throt);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_GPU_THROT_MASK, gpu_throt);
	r = REG_SET_MASK(r, THERMCTL_LVL0_CPU0_EN_MASK, 1);
	writel(r, ts->regs + reg_off);

	return 0;
}