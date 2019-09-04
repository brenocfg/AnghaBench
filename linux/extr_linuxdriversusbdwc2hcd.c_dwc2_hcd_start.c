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
struct dwc2_hsotg {scalar_t__ op_state; int /*<<< orphan*/  start_work; int /*<<< orphan*/  wq_otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPRT0 ; 
 int /*<<< orphan*/  HPRT0_RST ; 
 scalar_t__ OTG_STATE_B_HOST ; 
 int /*<<< orphan*/  dwc2_read_hprt0 (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dwc2_hcd_start(struct dwc2_hsotg *hsotg)
{
	u32 hprt0;

	if (hsotg->op_state == OTG_STATE_B_HOST) {
		/*
		 * Reset the port. During a HNP mode switch the reset
		 * needs to occur within 1ms and have a duration of at
		 * least 50ms.
		 */
		hprt0 = dwc2_read_hprt0(hsotg);
		hprt0 |= HPRT0_RST;
		dwc2_writel(hsotg, hprt0, HPRT0);
	}

	queue_delayed_work(hsotg->wq_otg, &hsotg->start_work,
			   msecs_to_jiffies(50));
}