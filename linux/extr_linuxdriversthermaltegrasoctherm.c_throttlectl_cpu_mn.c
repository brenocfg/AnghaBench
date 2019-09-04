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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* throt_cfgs; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;
struct TYPE_2__ {int cpu_throt_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THROTTLE_DEV_CPU ; 
 int THROT_DEPTH_DIVIDEND (int) ; 
 scalar_t__ THROT_PSKIP_CTRL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_DIVIDEND_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_DIVISOR_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_ENABLE_MASK ; 
 scalar_t__ THROT_PSKIP_RAMP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THROT_PSKIP_RAMP_DURATION_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_RAMP_STEP_MASK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void throttlectl_cpu_mn(struct tegra_soctherm *ts,
			       enum soctherm_throttle_id throt)
{
	u32 r;
	int depth;
	u8 dividend;

	depth = ts->throt_cfgs[throt].cpu_throt_depth;
	dividend = THROT_DEPTH_DIVIDEND(depth);

	r = readl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_DIVIDEND_MASK, dividend);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_DIVISOR_MASK, 0xff);
	writel(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_CPU));

	r = readl(ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
	r = REG_SET_MASK(r, THROT_PSKIP_RAMP_DURATION_MASK, 0xff);
	r = REG_SET_MASK(r, THROT_PSKIP_RAMP_STEP_MASK, 0xf);
	writel(r, ts->regs + THROT_PSKIP_RAMP(throt, THROTTLE_DEV_CPU));
}