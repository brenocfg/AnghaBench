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
struct TYPE_3__ {int port_suspend_change; int port_l1_change; } ;
struct TYPE_4__ {TYPE_1__ b; } ;
struct dwc2_hsotg {scalar_t__ lx_state; TYPE_2__ flags; int /*<<< orphan*/  priv; scalar_t__ bus_suspended; } ;

/* Variables and functions */
 scalar_t__ DWC2_L1 ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hcd_rem_wakeup(struct dwc2_hsotg *hsotg)
{
	if (hsotg->bus_suspended) {
		hsotg->flags.b.port_suspend_change = 1;
		usb_hcd_resume_root_hub(hsotg->priv);
	}

	if (hsotg->lx_state == DWC2_L1)
		hsotg->flags.b.port_l1_change = 1;
}