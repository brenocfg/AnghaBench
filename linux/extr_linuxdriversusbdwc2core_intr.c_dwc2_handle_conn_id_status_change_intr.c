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
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  wf_otg; scalar_t__ wq_otg; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GINTMSK ; 
 int /*<<< orphan*/  GINTSTS ; 
 int /*<<< orphan*/  GINTSTS_CONIDSTSCHNG ; 
 int /*<<< orphan*/  GINTSTS_SOF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ dwc2_is_host_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_handle_conn_id_status_change_intr(struct dwc2_hsotg *hsotg)
{
	u32 gintmsk;

	/* Clear interrupt */
	dwc2_writel(hsotg, GINTSTS_CONIDSTSCHNG, GINTSTS);

	/* Need to disable SOF interrupt immediately */
	gintmsk = dwc2_readl(hsotg, GINTMSK);
	gintmsk &= ~GINTSTS_SOF;
	dwc2_writel(hsotg, gintmsk, GINTMSK);

	dev_dbg(hsotg->dev, " ++Connector ID Status Change Interrupt++  (%s)\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device");

	/*
	 * Need to schedule a work, as there are possible DELAY function calls.
	 * Release lock before scheduling workq as it holds spinlock during
	 * scheduling.
	 */
	if (hsotg->wq_otg) {
		spin_unlock(&hsotg->lock);
		queue_work(hsotg->wq_otg, &hsotg->wf_otg);
		spin_lock(&hsotg->lock);
	}
}