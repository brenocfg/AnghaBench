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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct rndis_wlan_private {TYPE_1__ wdev; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  work; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  dev_poller_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disassociate (struct usbnet*,int) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  rndis_unbind (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rndis_wlan_unbind(struct usbnet *usbdev, struct usb_interface *intf)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);

	/* turn radio off */
	disassociate(usbdev, false);

	cancel_delayed_work_sync(&priv->dev_poller_work);
	cancel_delayed_work_sync(&priv->scan_work);
	cancel_work_sync(&priv->work);
	flush_workqueue(priv->workqueue);
	destroy_workqueue(priv->workqueue);

	rndis_unbind(usbdev, intf);

	wiphy_unregister(priv->wdev.wiphy);
	wiphy_free(priv->wdev.wiphy);
}