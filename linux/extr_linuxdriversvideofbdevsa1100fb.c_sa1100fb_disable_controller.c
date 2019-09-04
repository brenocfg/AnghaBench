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
typedef  int /*<<< orphan*/  u32 ;
struct sa1100fb_info {int /*<<< orphan*/  clk; int /*<<< orphan*/  ctrlr_wait; scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HZ ; 
 scalar_t__ LCCR0 ; 
 int /*<<< orphan*/  LCCR0_LDM ; 
 int /*<<< orphan*/  LCCR0_LEN ; 
 scalar_t__ LCSR ; 
 int /*<<< orphan*/  SHANNON_GPIO_DISP_EN ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_shannon () ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sa1100fb_disable_controller(struct sa1100fb_info *fbi)
{
	DECLARE_WAITQUEUE(wait, current);
	u32 lccr0;

	dev_dbg(fbi->dev, "Disabling LCD controller\n");

	if (machine_is_shannon())
		gpio_set_value(SHANNON_GPIO_DISP_EN, 0);

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&fbi->ctrlr_wait, &wait);

	/* Clear LCD Status Register */
	writel_relaxed(~0, fbi->base + LCSR);

	lccr0 = readl_relaxed(fbi->base + LCCR0);
	lccr0 &= ~LCCR0_LDM;	/* Enable LCD Disable Done Interrupt */
	writel_relaxed(lccr0, fbi->base + LCCR0);
	lccr0 &= ~LCCR0_LEN;	/* Disable LCD Controller */
	writel_relaxed(lccr0, fbi->base + LCCR0);

	schedule_timeout(20 * HZ / 1000);
	remove_wait_queue(&fbi->ctrlr_wait, &wait);

	/* disable LCD controller clock */
	clk_disable_unprepare(fbi->clk);
}