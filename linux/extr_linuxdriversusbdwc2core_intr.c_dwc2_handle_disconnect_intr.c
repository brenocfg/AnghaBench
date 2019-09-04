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
struct dwc2_hsotg {scalar_t__ op_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GINTSTS ; 
 int /*<<< orphan*/  GINTSTS_DISCONNINT ; 
 scalar_t__ OTG_STATE_A_HOST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_disconnect (struct dwc2_hsotg*,int) ; 
 scalar_t__ dwc2_is_host_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_op_state_str (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_handle_disconnect_intr(struct dwc2_hsotg *hsotg)
{
	dwc2_writel(hsotg, GINTSTS_DISCONNINT, GINTSTS);

	dev_dbg(hsotg->dev, "++Disconnect Detected Interrupt++ (%s) %s\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device",
		dwc2_op_state_str(hsotg));

	if (hsotg->op_state == OTG_STATE_A_HOST)
		dwc2_hcd_disconnect(hsotg, false);
}