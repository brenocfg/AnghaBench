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
typedef  long long u64 ;
typedef  int u32 ;
struct pxa168fb_info {scalar_t__ reg_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
struct fb_videomode {int /*<<< orphan*/  pixclock; int /*<<< orphan*/  refresh; } ;

/* Variables and functions */
 scalar_t__ LCD_CFG_SCLK_DIV ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void set_clock_divider(struct pxa168fb_info *fbi,
			      const struct fb_videomode *m)
{
	int divider_int;
	int needed_pixclk;
	u64 div_result;
	u32 x = 0;

	/*
	 * Notice: The field pixclock is used by linux fb
	 * is in pixel second. E.g. struct fb_videomode &
	 * struct fb_var_screeninfo
	 */

	/*
	 * Check input values.
	 */
	if (!m || !m->pixclock || !m->refresh) {
		dev_err(fbi->dev, "Input refresh or pixclock is wrong.\n");
		return;
	}

	/*
	 * Using PLL/AXI clock.
	 */
	x = 0x80000000;

	/*
	 * Calc divider according to refresh rate.
	 */
	div_result = 1000000000000ll;
	do_div(div_result, m->pixclock);
	needed_pixclk = (u32)div_result;

	divider_int = clk_get_rate(fbi->clk) / needed_pixclk;

	/* check whether divisor is too small. */
	if (divider_int < 2) {
		dev_warn(fbi->dev, "Warning: clock source is too slow."
				"Try smaller resolution\n");
		divider_int = 2;
	}

	/*
	 * Set setting to reg.
	 */
	x |= divider_int;
	writel(x, fbi->reg_base + LCD_CFG_SCLK_DIV);
}