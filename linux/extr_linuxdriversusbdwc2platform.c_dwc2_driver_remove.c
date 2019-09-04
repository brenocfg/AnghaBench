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
struct platform_device {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  reset_ecc; int /*<<< orphan*/  reset; scalar_t__ ll_hw_enabled; scalar_t__ gadget_enabled; scalar_t__ hcd_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_debugfs_exit (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hcd_remove (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_remove (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_lowlevel_hw_disable (struct dwc2_hsotg*) ; 
 struct dwc2_hsotg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_driver_remove(struct platform_device *dev)
{
	struct dwc2_hsotg *hsotg = platform_get_drvdata(dev);

	dwc2_debugfs_exit(hsotg);
	if (hsotg->hcd_enabled)
		dwc2_hcd_remove(hsotg);
	if (hsotg->gadget_enabled)
		dwc2_hsotg_remove(hsotg);

	if (hsotg->ll_hw_enabled)
		dwc2_lowlevel_hw_disable(hsotg);

	reset_control_assert(hsotg->reset);
	reset_control_assert(hsotg->reset_ecc);

	return 0;
}