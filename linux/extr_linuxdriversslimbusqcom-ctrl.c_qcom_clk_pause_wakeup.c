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
struct slim_controller {int /*<<< orphan*/  dev; } ;
struct qcom_slim_ctrl {scalar_t__ base; int /*<<< orphan*/  irq; int /*<<< orphan*/  rclk; int /*<<< orphan*/  hclk; } ;

/* Variables and functions */
 scalar_t__ FRM_WAKEUP ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct qcom_slim_ctrl* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int qcom_clk_pause_wakeup(struct slim_controller *sctrl)
{
	struct qcom_slim_ctrl *ctrl = dev_get_drvdata(sctrl->dev);

	clk_prepare_enable(ctrl->hclk);
	clk_prepare_enable(ctrl->rclk);
	enable_irq(ctrl->irq);

	writel_relaxed(1, ctrl->base + FRM_WAKEUP);
	/* Make sure framer wakeup write goes through before ISR fires */
	mb();
	/*
	 * HW Workaround: Currently, slave is reporting lost-sync messages
	 * after SLIMbus comes out of clock pause.
	 * Transaction with slave fail before slave reports that message
	 * Give some time for that report to come
	 * SLIMbus wakes up in clock gear 10 at 24.576MHz. With each superframe
	 * being 250 usecs, we wait for 5-10 superframes here to ensure
	 * we get the message
	 */
	usleep_range(1250, 2500);
	return 0;
}