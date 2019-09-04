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
struct usb_rx {struct usb_rx* buf; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (struct usb_rx*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_rx *alloc_rx_struct(void)
{
	struct usb_rx *r = NULL;
	int ret = 0;

	r = kmalloc(sizeof(*r), GFP_KERNEL);
	if (!r) {
		ret = -ENOMEM;
		goto out;
	}

	r->urb = usb_alloc_urb(0, GFP_KERNEL);
	r->buf = kmalloc(RX_BUF_SIZE, GFP_KERNEL);
	if (!r->urb || !r->buf) {
		ret = -ENOMEM;
		goto out;
	}
out:

	if (ret < 0) {
		if (r) {
			usb_free_urb(r->urb);
			kfree(r->buf);
			kfree(r);
		}
		return NULL;
	}

	return r;
}