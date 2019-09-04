#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  qtd_list; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 int DWC_E_INVALID ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_msleep (int) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_free (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_remove (TYPE_2__*,TYPE_1__*) ; 

int dwc_otg_hcd_endpoint_disable(dwc_otg_hcd_t * hcd, void *ep_handle,
				 int retry)
{
	dwc_otg_qh_t *qh = (dwc_otg_qh_t *) ep_handle;
	int retval = 0;
	dwc_irqflags_t flags;

	if (retry < 0) {
		retval = -DWC_E_INVALID;
		goto done;
	}

	if (!qh) {
		retval = -DWC_E_INVALID;
		goto done;
	}

	DWC_SPINLOCK_IRQSAVE(hcd->lock, &flags);

	while (!DWC_CIRCLEQ_EMPTY(&qh->qtd_list) && retry) {
		DWC_SPINUNLOCK_IRQRESTORE(hcd->lock, flags);
		retry--;
		dwc_msleep(5);
		DWC_SPINLOCK_IRQSAVE(hcd->lock, &flags);
	}

	dwc_otg_hcd_qh_remove(hcd, qh);

	DWC_SPINUNLOCK_IRQRESTORE(hcd->lock, flags);
	/*
	 * Split dwc_otg_hcd_qh_remove_and_free() into qh_remove
	 * and qh_free to prevent stack dump on DWC_DMA_FREE() with
	 * irq_disabled (spinlock_irqsave) in dwc_otg_hcd_desc_list_free()
	 * and dwc_otg_hcd_frame_list_alloc().
	 */
	dwc_otg_hcd_qh_free(hcd, qh);

done:
	return retval;
}