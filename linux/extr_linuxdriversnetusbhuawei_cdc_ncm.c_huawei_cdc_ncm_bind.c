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
struct usbnet {TYPE_1__* status; int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct huawei_cdc_ncm_state {struct usb_driver* subdriver; struct cdc_ncm_ctx* ctx; } ;
struct cdc_ncm_ctx {int /*<<< orphan*/  control; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int CDC_NCM_FLAG_NDP_TO_END ; 
 int CDC_NCM_FLAG_RESET_NTB16 ; 
 int ENODEV ; 
 struct usb_driver* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct usb_driver*) ; 
 int PTR_ERR (struct usb_driver*) ; 
 int cdc_ncm_bind_common (struct usbnet*,struct usb_interface*,int,int) ; 
 int /*<<< orphan*/  cdc_ncm_unbind (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  huawei_cdc_ncm_wdm_manage_power ; 
 struct usb_driver* usb_cdc_wdm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int huawei_cdc_ncm_bind(struct usbnet *usbnet_dev,
			       struct usb_interface *intf)
{
	struct cdc_ncm_ctx *ctx;
	struct usb_driver *subdriver = ERR_PTR(-ENODEV);
	int ret = -ENODEV;
	struct huawei_cdc_ncm_state *drvstate = (void *)&usbnet_dev->data;
	int drvflags = 0;

	/* altsetting should always be 1 for NCM devices - so we hard-coded
	 * it here. Some huawei devices will need the NDP part of the NCM package to
	 * be at the end of the frame.
	 */
	drvflags |= CDC_NCM_FLAG_NDP_TO_END;

	/* Additionally, it has been reported that some Huawei E3372H devices, with
	 * firmware version 21.318.01.00.541, come out of reset in NTB32 format mode, hence
	 * needing to be set to the NTB16 one again.
	 */
	drvflags |= CDC_NCM_FLAG_RESET_NTB16;
	ret = cdc_ncm_bind_common(usbnet_dev, intf, 1, drvflags);
	if (ret)
		goto err;

	ctx = drvstate->ctx;

	if (usbnet_dev->status)
		/* The wMaxCommand buffer must be big enough to hold
		 * any message from the modem. Experience has shown
		 * that some replies are more than 256 bytes long
		 */
		subdriver = usb_cdc_wdm_register(ctx->control,
						 &usbnet_dev->status->desc,
						 1024, /* wMaxCommand */
						 huawei_cdc_ncm_wdm_manage_power);
	if (IS_ERR(subdriver)) {
		ret = PTR_ERR(subdriver);
		cdc_ncm_unbind(usbnet_dev, intf);
		goto err;
	}

	/* Prevent usbnet from using the status descriptor */
	usbnet_dev->status = NULL;

	drvstate->subdriver = subdriver;

err:
	return ret;
}