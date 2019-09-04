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
struct usbnet {scalar_t__* data; int /*<<< orphan*/  net; } ;
struct usb_interface {int dummy; } ;
struct smsc75xx_priv {int /*<<< orphan*/  set_multicast; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  kfree (struct smsc75xx_priv*) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void smsc75xx_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct smsc75xx_priv *pdata = (struct smsc75xx_priv *)(dev->data[0]);
	if (pdata) {
		cancel_work_sync(&pdata->set_multicast);
		netif_dbg(dev, ifdown, dev->net, "free pdata\n");
		kfree(pdata);
		pdata = NULL;
		dev->data[0] = 0;
	}
}