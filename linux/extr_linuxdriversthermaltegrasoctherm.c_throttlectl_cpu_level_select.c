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
typedef  int u32 ;
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* throt_cfgs; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;
struct TYPE_2__ {int cpu_throt_level; } ;

/* Variables and functions */
 int REG_SET_MASK (int,int /*<<< orphan*/ ,int) ; 
#define  TEGRA_SOCTHERM_THROT_LEVEL_HIGH 130 
#define  TEGRA_SOCTHERM_THROT_LEVEL_LOW 129 
#define  TEGRA_SOCTHERM_THROT_LEVEL_MED 128 
 int /*<<< orphan*/  THROTTLE_DEV_CPU ; 
 scalar_t__ THROT_PSKIP_CTRL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_ENABLE_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_VECT2_CPU_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_VECT_CPU_MASK ; 
 scalar_t__ THROT_PSKIP_RAMP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THROT_PSKIP_RAMP_SEQ_BYPASS_MODE_MASK ; 
 int THROT_VECT_HIGH ; 
 int THROT_VECT_LOW ; 
 int THROT_VECT_MED ; 
 int THROT_VECT_NONE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void throttlectl_cpu_level_select(struct tegra_soctherm *ts,
					 enum soctherm_throttle_id throt)
{
	u32 r, throt_vect;

	/* Denver:CCROC NV_THERM interface N:3 Mapping */
	switch (ts->throt_cfgs[throt].cpu_throt_level) {
	case TEGRA_SOCTHERM_THROT_LEVEL_LOW:
		throt_vect = THROT_VECT_LOW;
		break;
	case TEGRA_SOCTHERM_THROT_LEVEL_MED:
		throt_vect = THROT_VECT_MED;
		break;
	case TEGRA_SOCTHERM_THROT_LEVEL_HIGH:
		throt_vect = THROT_VECT_HIGH;
		break;
	default:
		throt_vect = THROT_VECT_NONE;
		break;
	}

	r = readl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT_CPU_MASK, throt_vect);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT2_CPU_MASK, throt_vect);
	writel(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));

	/* bypass sequencer in soc_therm as it is programmed in ccroc */
	r = REG_SET_MASK(0, THROT_PSKIP_RAMP_SEQ_BYPASS_MODE_MASK, 1);
	writel(r, ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
}