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
struct usbnet {int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct huawei_cdc_ncm_state {TYPE_1__* subdriver; struct cdc_ncm_ctx* ctx; } ;
struct cdc_ncm_ctx {int /*<<< orphan*/  control; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cdc_ncm_unbind (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void huawei_cdc_ncm_unbind(struct usbnet *usbnet_dev,
				  struct usb_interface *intf)
{
	struct huawei_cdc_ncm_state *drvstate = (void *)&usbnet_dev->data;
	struct cdc_ncm_ctx *ctx = drvstate->ctx;

	if (drvstate->subdriver && drvstate->subdriver->disconnect)
		drvstate->subdriver->disconnect(ctx->control);
	drvstate->subdriver = NULL;

	cdc_ncm_unbind(usbnet_dev, intf);
}