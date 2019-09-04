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
struct usb_rx {int (* callback ) (void*,void*,int,int) ;int /*<<< orphan*/  rx_submit_list; int /*<<< orphan*/  urb; int /*<<< orphan*/  buf; struct rx_cxt* rx; void* index; void* cb_data; } ;
struct usb_device {int dummy; } ;
struct rx_cxt {int /*<<< orphan*/  submit_lock; int /*<<< orphan*/  rx_submit_list; } ;
struct lte_udev {int (* rx_cb ) (void*,void*,int,int) ;struct usb_device* usbdev; struct rx_cxt rx; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KERNEL_THREAD ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  gdm_usb_rcv_complete ; 
 struct usb_rx* get_rx_struct (struct rx_cxt*,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put_rx_struct (struct rx_cxt*,struct usb_rx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_rx*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdm_usb_recv(void *priv_dev,
			int (*cb)(void *cb_data,
				  void *data, int len, int context),
			void *cb_data,
			int context)
{
	struct lte_udev *udev = priv_dev;
	struct usb_device *usbdev = udev->usbdev;
	struct rx_cxt *rx = &udev->rx;
	struct usb_rx *r;
	int no_spc;
	int ret;
	unsigned long flags;

	if (!udev->usbdev) {
		pr_err("invalid device\n");
		return -ENODEV;
	}

	r = get_rx_struct(rx, &no_spc);
	if (!r) {
		pr_err("Out of Memory\n");
		return -ENOMEM;
	}

	udev->rx_cb = cb;
	r->callback = cb;
	r->cb_data = cb_data;
	r->index = (void *)udev;
	r->rx = rx;

	usb_fill_bulk_urb(r->urb,
			  usbdev,
			  usb_rcvbulkpipe(usbdev, 0x83),
			  r->buf,
			  RX_BUF_SIZE,
			  gdm_usb_rcv_complete,
			  r);

	spin_lock_irqsave(&rx->submit_lock, flags);
	list_add_tail(&r->rx_submit_list, &rx->rx_submit_list);
	spin_unlock_irqrestore(&rx->submit_lock, flags);

	if (context == KERNEL_THREAD)
		ret = usb_submit_urb(r->urb, GFP_KERNEL);
	else
		ret = usb_submit_urb(r->urb, GFP_ATOMIC);

	if (ret) {
		spin_lock_irqsave(&rx->submit_lock, flags);
		list_del(&r->rx_submit_list);
		spin_unlock_irqrestore(&rx->submit_lock, flags);

		pr_err("usb_submit_urb failed (%p)\n", r);
		put_rx_struct(rx, r);
	}

	return ret;
}