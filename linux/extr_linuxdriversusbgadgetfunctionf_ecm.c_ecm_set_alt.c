#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  cdc_filter; int /*<<< orphan*/  is_zlp_ok; TYPE_2__* out_ep; TYPE_2__* in_ep; } ;
struct f_ecm {unsigned int ctrl_id; unsigned int data_id; TYPE_4__ port; TYPE_2__* notify; } ;
struct TYPE_8__ {int /*<<< orphan*/ * desc; scalar_t__ enabled; } ;
struct TYPE_7__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  DEFAULT_FILTER ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,unsigned int) ; 
 scalar_t__ config_ep_by_speed (int /*<<< orphan*/ ,struct usb_function*,TYPE_2__*) ; 
 int /*<<< orphan*/  ecm_notify (struct f_ecm*) ; 
 struct f_ecm* func_to_ecm (struct usb_function*) ; 
 int /*<<< orphan*/  gadget_is_zlp_supported (int /*<<< orphan*/ ) ; 
 struct net_device* gether_connect (TYPE_4__*) ; 
 int /*<<< orphan*/  gether_disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_ep_enable (TYPE_2__*) ; 

__attribute__((used)) static int ecm_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_ecm		*ecm = func_to_ecm(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	/* Control interface has only altsetting 0 */
	if (intf == ecm->ctrl_id) {
		if (alt != 0)
			goto fail;

		VDBG(cdev, "reset ecm control %d\n", intf);
		usb_ep_disable(ecm->notify);
		if (!(ecm->notify->desc)) {
			VDBG(cdev, "init ecm ctrl %d\n", intf);
			if (config_ep_by_speed(cdev->gadget, f, ecm->notify))
				goto fail;
		}
		usb_ep_enable(ecm->notify);

	/* Data interface has two altsettings, 0 and 1 */
	} else if (intf == ecm->data_id) {
		if (alt > 1)
			goto fail;

		if (ecm->port.in_ep->enabled) {
			DBG(cdev, "reset ecm\n");
			gether_disconnect(&ecm->port);
		}

		if (!ecm->port.in_ep->desc ||
		    !ecm->port.out_ep->desc) {
			DBG(cdev, "init ecm\n");
			if (config_ep_by_speed(cdev->gadget, f,
					       ecm->port.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       ecm->port.out_ep)) {
				ecm->port.in_ep->desc = NULL;
				ecm->port.out_ep->desc = NULL;
				goto fail;
			}
		}

		/* CDC Ethernet only sends data in non-default altsettings.
		 * Changing altsettings resets filters, statistics, etc.
		 */
		if (alt == 1) {
			struct net_device	*net;

			/* Enable zlps by default for ECM conformance;
			 * override for musb_hdrc (avoids txdma ovhead).
			 */
			ecm->port.is_zlp_ok =
				gadget_is_zlp_supported(cdev->gadget);
			ecm->port.cdc_filter = DEFAULT_FILTER;
			DBG(cdev, "activate ecm\n");
			net = gether_connect(&ecm->port);
			if (IS_ERR(net))
				return PTR_ERR(net);
		}

		/* NOTE this can be a minor disagreement with the ECM spec,
		 * which says speed notifications will "always" follow
		 * connection notifications.  But we allow one connect to
		 * follow another (if the first is in flight), and instead
		 * just guarantee that a speed notification is always sent.
		 */
		ecm_notify(ecm);
	} else
		goto fail;

	return 0;
fail:
	return -EINVAL;
}