#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfcmrvl_usb_drv_data {int /*<<< orphan*/  deferred; TYPE_1__* intf; int /*<<< orphan*/  tx_anchor; int /*<<< orphan*/  flags; int /*<<< orphan*/  waker; } ;
struct nfcmrvl_private {struct nfcmrvl_usb_drv_data* drv_data; } ;
struct TYPE_3__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFCMRVL_USB_BULK_RUNNING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfcmrvl_usb_stop_traffic (struct nfcmrvl_usb_drv_data*) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfcmrvl_usb_nci_close(struct nfcmrvl_private *priv)
{
	struct nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	int err;

	cancel_work_sync(&drv_data->waker);

	clear_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags);

	nfcmrvl_usb_stop_traffic(drv_data);
	usb_kill_anchored_urbs(&drv_data->tx_anchor);
	err = usb_autopm_get_interface(drv_data->intf);
	if (err)
		goto failed;

	drv_data->intf->needs_remote_wakeup = 0;
	usb_autopm_put_interface(drv_data->intf);

failed:
	usb_scuttle_anchored_urbs(&drv_data->deferred);
	return 0;
}