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
struct lbtf_private {int dummy; } ;
struct if_usb_card {struct lbtf_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_MAIN ; 
 int /*<<< orphan*/  if_usb_free (struct if_usb_card*) ; 
 int /*<<< orphan*/  if_usb_reset_device (struct if_usb_card*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_remove_card (struct lbtf_private*) ; 
 struct if_usb_card* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_disconnect(struct usb_interface *intf)
{
	struct if_usb_card *cardp = usb_get_intfdata(intf);
	struct lbtf_private *priv = cardp->priv;

	lbtf_deb_enter(LBTF_DEB_MAIN);

	if_usb_reset_device(cardp);

	if (priv)
		lbtf_remove_card(priv);

	/* Unlink and free urb */
	if_usb_free(cardp);

	usb_set_intfdata(intf, NULL);
	usb_put_dev(interface_to_usbdev(intf));

	lbtf_deb_leave(LBTF_DEB_MAIN);
}