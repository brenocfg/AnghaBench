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
struct usbnet {TYPE_1__* intf; int /*<<< orphan*/  net; scalar_t__* data; } ;
struct smsc95xx_priv {int features; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int FEATURE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 

__attribute__((used)) static int smsc95xx_manage_power(struct usbnet *dev, int on)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);

	dev->intf->needs_remote_wakeup = on;

	if (pdata->features & FEATURE_REMOTE_WAKEUP)
		return 0;

	/* this chip revision isn't capable of remote wakeup */
	netdev_info(dev->net, "hardware isn't capable of remote wakeup\n");

	if (on)
		usb_autopm_get_interface_no_resume(dev->intf);
	else
		usb_autopm_put_interface(dev->intf);

	return 0;
}