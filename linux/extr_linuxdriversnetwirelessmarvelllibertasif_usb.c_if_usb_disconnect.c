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
struct usb_interface {int dummy; } ;
struct lbs_private {int dummy; } ;
struct if_usb_card {int surprise_removed; struct lbs_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_usb_free (struct if_usb_card*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lbs_remove_card (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_stop_card (struct lbs_private*) ; 
 struct if_usb_card* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_disconnect(struct usb_interface *intf)
{
	struct if_usb_card *cardp = usb_get_intfdata(intf);
	struct lbs_private *priv = cardp->priv;

	cardp->surprise_removed = 1;

	if (priv) {
		lbs_stop_card(priv);
		lbs_remove_card(priv);
	}

	/* Unlink and free urb */
	if_usb_free(cardp);

	usb_set_intfdata(intf, NULL);
	usb_put_dev(interface_to_usbdev(intf));
}