#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GET_CORE_IF (TYPE_1__*) ; 
 scalar_t__ dwc_otg_is_device_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_pcd_rem_wkup_from_suspend (TYPE_1__*,int) ; 

void dwc_otg_pcd_remote_wakeup(dwc_otg_pcd_t * pcd, int set)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_irqflags_t flags;
	if (dwc_otg_is_device_mode(core_if)) {
		DWC_SPINLOCK_IRQSAVE(pcd->lock, &flags);
#ifdef CONFIG_USB_DWC_OTG_LPM
		if (core_if->lx_state == DWC_OTG_L1) {
			dwc_otg_pcd_rem_wkup_from_sleep(pcd, set);
		} else {
#endif
			dwc_otg_pcd_rem_wkup_from_suspend(pcd, set);
#ifdef CONFIG_USB_DWC_OTG_LPM
		}
#endif
		DWC_SPINUNLOCK_IRQRESTORE(pcd->lock, flags);
	}
	return;
}