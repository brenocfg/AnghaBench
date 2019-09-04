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
typedef  int uint32_t ;
struct jzfb {int /*<<< orphan*/  ldclk; TYPE_1__* pdev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int JZ_LCD_CTRL_DISABLE ; 
 int JZ_LCD_STATE_DISABLED ; 
 scalar_t__ JZ_REG_LCD_CTRL ; 
 scalar_t__ JZ_REG_LCD_STATE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void jzfb_disable(struct jzfb *jzfb)
{
	uint32_t ctrl;

	ctrl = readl(jzfb->base + JZ_REG_LCD_CTRL);
	ctrl |= JZ_LCD_CTRL_DISABLE;
	writel(ctrl, jzfb->base + JZ_REG_LCD_CTRL);
	do {
		ctrl = readl(jzfb->base + JZ_REG_LCD_STATE);
	} while (!(ctrl & JZ_LCD_STATE_DISABLED));

	pinctrl_pm_select_sleep_state(&jzfb->pdev->dev);

	clk_disable_unprepare(jzfb->ldclk);
}