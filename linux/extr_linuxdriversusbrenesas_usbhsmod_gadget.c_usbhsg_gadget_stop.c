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
struct usbhsg_gpriv {int /*<<< orphan*/ * driver; TYPE_1__* transceiver; } ;
struct usbhs_priv {int dummy; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  USBHSG_STATUS_REGISTERD ; 
 int /*<<< orphan*/  otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usbhsg_gpriv* usbhsg_gadget_to_gpriv (struct usb_gadget*) ; 
 struct usbhs_priv* usbhsg_gpriv_to_priv (struct usbhsg_gpriv*) ; 
 int /*<<< orphan*/  usbhsg_try_stop (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsg_gadget_stop(struct usb_gadget *gadget)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	usbhsg_try_stop(priv, USBHSG_STATUS_REGISTERD);

	if (!IS_ERR_OR_NULL(gpriv->transceiver))
		otg_set_peripheral(gpriv->transceiver->otg, NULL);

	gpriv->driver = NULL;

	return 0;
}