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
struct usbnet {struct asix_common_private* driver_priv; } ;
struct usb_interface {int dummy; } ;
struct asix_common_private {int /*<<< orphan*/  (* suspend ) (struct usbnet*) ;} ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usbnet*) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_suspend (struct usb_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asix_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usbnet *dev = usb_get_intfdata(intf);
	struct asix_common_private *priv = dev->driver_priv;

	if (priv && priv->suspend)
		priv->suspend(dev);

	return usbnet_suspend(intf, message);
}