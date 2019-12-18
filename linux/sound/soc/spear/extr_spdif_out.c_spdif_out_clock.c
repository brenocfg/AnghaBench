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
struct spdif_out_dev {scalar_t__ io_base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int SPDIF_DIVIDER_MASK ; 
 int SPDIF_DIVIDER_SHIFT ; 
 scalar_t__ SPDIF_OUT_CTRL ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spdif_out_clock(struct spdif_out_dev *host, u32 core_freq,
		u32 rate)
{
	u32 divider, ctrl;

	clk_set_rate(host->clk, core_freq);
	divider = DIV_ROUND_CLOSEST(clk_get_rate(host->clk), (rate * 128));

	ctrl = readl(host->io_base + SPDIF_OUT_CTRL);
	ctrl &= ~SPDIF_DIVIDER_MASK;
	ctrl |= (divider << SPDIF_DIVIDER_SHIFT) & SPDIF_DIVIDER_MASK;
	writel(ctrl, host->io_base + SPDIF_OUT_CTRL);
}