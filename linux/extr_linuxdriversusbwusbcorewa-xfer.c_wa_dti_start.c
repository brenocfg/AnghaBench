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
struct wahc {int /*<<< orphan*/ * dti_urb; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/ * buf_in_urbs; int /*<<< orphan*/  dti_buf_size; int /*<<< orphan*/ * dti_buf; TYPE_1__* usb_iface; struct usb_endpoint_descriptor* dti_epd; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WA_MAX_BUF_IN_URBS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wahc*) ; 
 int /*<<< orphan*/  usb_put_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_buf_in_cb ; 
 int /*<<< orphan*/  wa_dti_cb ; 

int wa_dti_start(struct wahc *wa)
{
	const struct usb_endpoint_descriptor *dti_epd = wa->dti_epd;
	struct device *dev = &wa->usb_iface->dev;
	int result = -ENOMEM, index;

	if (wa->dti_urb != NULL)	/* DTI URB already started */
		goto out;

	wa->dti_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (wa->dti_urb == NULL)
		goto error_dti_urb_alloc;
	usb_fill_bulk_urb(
		wa->dti_urb, wa->usb_dev,
		usb_rcvbulkpipe(wa->usb_dev, 0x80 | dti_epd->bEndpointAddress),
		wa->dti_buf, wa->dti_buf_size,
		wa_dti_cb, wa);

	/* init the buf in URBs */
	for (index = 0; index < WA_MAX_BUF_IN_URBS; ++index) {
		usb_fill_bulk_urb(
			&(wa->buf_in_urbs[index]), wa->usb_dev,
			usb_rcvbulkpipe(wa->usb_dev,
				0x80 | dti_epd->bEndpointAddress),
			NULL, 0, wa_buf_in_cb, wa);
	}
	result = usb_submit_urb(wa->dti_urb, GFP_KERNEL);
	if (result < 0) {
		dev_err(dev, "DTI Error: Could not submit DTI URB (%d) resetting\n",
			result);
		goto error_dti_urb_submit;
	}
out:
	return 0;

error_dti_urb_submit:
	usb_put_urb(wa->dti_urb);
	wa->dti_urb = NULL;
error_dti_urb_alloc:
	return result;
}