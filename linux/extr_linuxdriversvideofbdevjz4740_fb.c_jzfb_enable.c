#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct jzfb {scalar_t__ base; TYPE_2__* framedesc; TYPE_1__* pdev; int /*<<< orphan*/  ldclk; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_LCD_CTRL_DISABLE ; 
 int /*<<< orphan*/  JZ_LCD_CTRL_ENABLE ; 
 scalar_t__ JZ_REG_LCD_CTRL ; 
 scalar_t__ JZ_REG_LCD_DA0 ; 
 scalar_t__ JZ_REG_LCD_STATE ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jzfb_enable(struct jzfb *jzfb)
{
	uint32_t ctrl;

	clk_prepare_enable(jzfb->ldclk);

	pinctrl_pm_select_default_state(&jzfb->pdev->dev);

	writel(0, jzfb->base + JZ_REG_LCD_STATE);

	writel(jzfb->framedesc->next, jzfb->base + JZ_REG_LCD_DA0);

	ctrl = readl(jzfb->base + JZ_REG_LCD_CTRL);
	ctrl |= JZ_LCD_CTRL_ENABLE;
	ctrl &= ~JZ_LCD_CTRL_DISABLE;
	writel(ctrl, jzfb->base + JZ_REG_LCD_CTRL);
}