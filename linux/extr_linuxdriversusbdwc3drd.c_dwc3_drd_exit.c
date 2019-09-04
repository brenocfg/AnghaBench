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
struct dwc3 {int current_dr_role; int /*<<< orphan*/  otg_irq; scalar_t__ edev; int /*<<< orphan*/  lock; int /*<<< orphan*/  desired_otg_role; int /*<<< orphan*/  drd_work; int /*<<< orphan*/  edev_nb; } ;

/* Variables and functions */
#define  DWC3_GCTL_PRTCAP_DEVICE 130 
#define  DWC3_GCTL_PRTCAP_HOST 129 
#define  DWC3_GCTL_PRTCAP_OTG 128 
 int /*<<< orphan*/  DWC3_OTG_ROLE_IDLE ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc3_event_buffers_cleanup (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_exit (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_host_exit (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_exit (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_update (struct dwc3*,int) ; 
 int /*<<< orphan*/  extcon_unregister_notifier (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dwc3*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dwc3_drd_exit(struct dwc3 *dwc)
{
	unsigned long flags;

	if (dwc->edev)
		extcon_unregister_notifier(dwc->edev, EXTCON_USB_HOST,
					   &dwc->edev_nb);

	cancel_work_sync(&dwc->drd_work);

	/* debug user might have changed role, clean based on current role */
	switch (dwc->current_dr_role) {
	case DWC3_GCTL_PRTCAP_HOST:
		dwc3_host_exit(dwc);
		break;
	case DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_gadget_exit(dwc);
		dwc3_event_buffers_cleanup(dwc);
		break;
	case DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_exit(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc->desired_otg_role = DWC3_OTG_ROLE_IDLE;
		spin_unlock_irqrestore(&dwc->lock, flags);
		dwc3_otg_update(dwc, 1);
		break;
	default:
		break;
	}

	if (!dwc->edev)
		free_irq(dwc->otg_irq, dwc);
}