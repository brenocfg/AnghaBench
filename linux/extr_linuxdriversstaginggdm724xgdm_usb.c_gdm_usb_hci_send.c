#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_tx {void (* callback ) (void*) ;int len; int /*<<< orphan*/  list; scalar_t__ is_sdu; struct tx_cxt* tx; void* cb_data; int /*<<< orphan*/  buf; } ;
struct tx_cxt {int /*<<< orphan*/  lock; int /*<<< orphan*/  hci_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct lte_udev {TYPE_1__ work_tx; int /*<<< orphan*/  usbdev; struct tx_cxt tx; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct usb_tx* alloc_tx_struct (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gdm_usb_hci_send(void *priv_dev, void *data, int len,
			    void (*cb)(void *data), void *cb_data)
{
	struct lte_udev *udev = priv_dev;
	struct tx_cxt *tx = &udev->tx;
	struct usb_tx *t;
	unsigned long flags;

	if (!udev->usbdev) {
		pr_err("hci send - invalid device\n");
		return -ENODEV;
	}

	t = alloc_tx_struct(len);
	if (!t) {
		pr_err("hci_send - out of memory\n");
		return -ENOMEM;
	}

	memcpy(t->buf, data, len);
	t->callback = cb;
	t->cb_data = cb_data;
	t->len = len;
	t->tx = tx;
	t->is_sdu = 0;

	spin_lock_irqsave(&tx->lock, flags);
	list_add_tail(&t->list, &tx->hci_list);
	schedule_work(&udev->work_tx.work);
	spin_unlock_irqrestore(&tx->lock, flags);

	return 0;
}