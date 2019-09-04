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
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPRT0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_disable_host_interrupts (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dwc2_hcd_stop(struct dwc2_hsotg *hsotg)
{
	dev_dbg(hsotg->dev, "DWC OTG HCD STOP\n");

	/*
	 * The root hub should be disconnected before this function is called.
	 * The disconnect will clear the QTD lists (via ..._hcd_urb_dequeue)
	 * and the QH lists (via ..._hcd_endpoint_disable).
	 */

	/* Turn off all host-specific interrupts */
	dwc2_disable_host_interrupts(hsotg);

	/* Turn off the vbus power */
	dev_dbg(hsotg->dev, "PortPower off\n");
	dwc2_writel(hsotg, 0, HPRT0);
}