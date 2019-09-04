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
struct usbnet {scalar_t__* data; } ;
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct cdc_ncm_ctx {struct usb_interface* control; struct usb_interface* data; int /*<<< orphan*/  bh; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cdc_ncm_free (struct cdc_ncm_ctx*) ; 
 struct usb_driver* driver_of (struct usb_interface*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void cdc_ncm_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	struct usb_driver *driver = driver_of(intf);

	if (ctx == NULL)
		return;		/* no setup */

	atomic_set(&ctx->stop, 1);

	hrtimer_cancel(&ctx->tx_timer);

	tasklet_kill(&ctx->bh);

	/* handle devices with combined control and data interface */
	if (ctx->control == ctx->data)
		ctx->data = NULL;

	/* disconnect master --> disconnect slave */
	if (intf == ctx->control && ctx->data) {
		usb_set_intfdata(ctx->data, NULL);
		usb_driver_release_interface(driver, ctx->data);
		ctx->data = NULL;

	} else if (intf == ctx->data && ctx->control) {
		usb_set_intfdata(ctx->control, NULL);
		usb_driver_release_interface(driver, ctx->control);
		ctx->control = NULL;
	}

	usb_set_intfdata(intf, NULL);
	cdc_ncm_free(ctx);
}