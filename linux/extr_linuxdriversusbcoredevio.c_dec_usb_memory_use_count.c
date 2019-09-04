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
struct usb_memory {scalar_t__ urb_use_count; scalar_t__ vma_use_count; scalar_t__ size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  mem; int /*<<< orphan*/  memlist; struct usb_dev_state* ps; } ;
struct usb_dev_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_memory*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbfs_decrease_memory_usage (scalar_t__) ; 

__attribute__((used)) static void dec_usb_memory_use_count(struct usb_memory *usbm, int *count)
{
	struct usb_dev_state *ps = usbm->ps;
	unsigned long flags;

	spin_lock_irqsave(&ps->lock, flags);
	--*count;
	if (usbm->urb_use_count == 0 && usbm->vma_use_count == 0) {
		list_del(&usbm->memlist);
		spin_unlock_irqrestore(&ps->lock, flags);

		usb_free_coherent(ps->dev, usbm->size, usbm->mem,
				usbm->dma_handle);
		usbfs_decrease_memory_usage(
			usbm->size + sizeof(struct usb_memory));
		kfree(usbm);
	} else {
		spin_unlock_irqrestore(&ps->lock, flags);
	}
}