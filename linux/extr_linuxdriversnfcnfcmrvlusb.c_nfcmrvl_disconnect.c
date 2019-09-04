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
struct usb_interface {int dummy; } ;
struct nfcmrvl_usb_drv_data {int /*<<< orphan*/  intf; int /*<<< orphan*/  priv; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ *,char*,struct usb_interface*) ; 
 int /*<<< orphan*/  nfcmrvl_nci_unregister_dev (int /*<<< orphan*/ ) ; 
 struct nfcmrvl_usb_drv_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfcmrvl_disconnect(struct usb_interface *intf)
{
	struct nfcmrvl_usb_drv_data *drv_data = usb_get_intfdata(intf);

	if (!drv_data)
		return;

	nfc_info(&drv_data->udev->dev, "intf %p\n", intf);

	nfcmrvl_nci_unregister_dev(drv_data->priv);

	usb_set_intfdata(drv_data->intf, NULL);
}