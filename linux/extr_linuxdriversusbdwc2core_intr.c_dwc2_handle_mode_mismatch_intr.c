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
 int /*<<< orphan*/  GINTSTS ; 
 int /*<<< orphan*/  GINTSTS_MODEMIS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ dwc2_is_host_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_handle_mode_mismatch_intr(struct dwc2_hsotg *hsotg)
{
	/* Clear interrupt */
	dwc2_writel(hsotg, GINTSTS_MODEMIS, GINTSTS);

	dev_warn(hsotg->dev, "Mode Mismatch Interrupt: currently in %s mode\n",
		 dwc2_is_host_mode(hsotg) ? "Host" : "Device");
}