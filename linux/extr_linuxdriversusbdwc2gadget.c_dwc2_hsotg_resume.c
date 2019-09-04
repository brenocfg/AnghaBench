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
struct dwc2_hsotg {scalar_t__ lx_state; int /*<<< orphan*/  lock; scalar_t__ enabled; TYPE_2__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 scalar_t__ DWC2_L2 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_enable_acg (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_core_connect (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_core_init_disconnected (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dwc2_hsotg_resume(struct dwc2_hsotg *hsotg)
{
	unsigned long flags;

	if (hsotg->lx_state == DWC2_L2)
		return 0;

	if (hsotg->driver) {
		dev_info(hsotg->dev, "resuming usb gadget %s\n",
			 hsotg->driver->driver.name);

		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_hsotg_core_init_disconnected(hsotg, false);
		if (hsotg->enabled) {
			/* Enable ACG feature in device mode,if supported */
			dwc2_enable_acg(hsotg);
			dwc2_hsotg_core_connect(hsotg);
		}
		spin_unlock_irqrestore(&hsotg->lock, flags);
	}

	return 0;
}