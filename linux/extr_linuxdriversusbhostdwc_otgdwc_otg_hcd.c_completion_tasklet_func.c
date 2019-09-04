#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct urb* urb; } ;
typedef  TYPE_1__ urb_tq_entry_t ;
struct urb {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  priv; int /*<<< orphan*/  completed_urb_list; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* DWC_TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urb_tq_entries ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void completion_tasklet_func(void *ptr)
{
	dwc_otg_hcd_t *hcd = (dwc_otg_hcd_t *) ptr;
	struct urb *urb;
	urb_tq_entry_t *item;
	dwc_irqflags_t flags;

	/* This could just be spin_lock_irq */
	DWC_SPINLOCK_IRQSAVE(hcd->lock, &flags);
	while (!DWC_TAILQ_EMPTY(&hcd->completed_urb_list)) {
		item = DWC_TAILQ_FIRST(&hcd->completed_urb_list);
		urb = item->urb;
		DWC_TAILQ_REMOVE(&hcd->completed_urb_list, item,
				urb_tq_entries);
		DWC_SPINUNLOCK_IRQRESTORE(hcd->lock, flags);
		DWC_FREE(item);

		usb_hcd_giveback_urb(hcd->priv, urb, urb->status);


		DWC_SPINLOCK_IRQSAVE(hcd->lock, &flags);
	}
	DWC_SPINUNLOCK_IRQRESTORE(hcd->lock, flags);
	return;
}