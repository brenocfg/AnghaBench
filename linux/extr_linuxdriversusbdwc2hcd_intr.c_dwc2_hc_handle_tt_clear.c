#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct urb {TYPE_3__* dev; } ;
struct dwc2_qtd {TYPE_4__* urb; } ;
struct dwc2_hsotg {int dummy; } ;
struct dwc2_host_chan {TYPE_5__* qh; } ;
struct TYPE_7__ {struct usb_device* root_hub; } ;
struct TYPE_12__ {TYPE_1__ self; } ;
struct TYPE_11__ {scalar_t__ dev_speed; int tt_buffer_dirty; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; struct urb* priv; } ;
struct TYPE_9__ {TYPE_2__* tt; } ;
struct TYPE_8__ {struct usb_device* hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  EREMOTEIO ; 
 scalar_t__ USB_SPEED_HIGH ; 
 TYPE_6__* dwc2_hsotg_to_hcd (struct dwc2_hsotg*) ; 
 scalar_t__ usb_hub_clear_tt_buffer (struct urb*) ; 

__attribute__((used)) static void dwc2_hc_handle_tt_clear(struct dwc2_hsotg *hsotg,
				    struct dwc2_host_chan *chan,
				    struct dwc2_qtd *qtd)
{
	struct usb_device *root_hub = dwc2_hsotg_to_hcd(hsotg)->self.root_hub;
	struct urb *usb_urb;

	if (!chan->qh)
		return;

	if (chan->qh->dev_speed == USB_SPEED_HIGH)
		return;

	if (!qtd->urb)
		return;

	usb_urb = qtd->urb->priv;
	if (!usb_urb || !usb_urb->dev || !usb_urb->dev->tt)
		return;

	/*
	 * The root hub doesn't really have a TT, but Linux thinks it
	 * does because how could you have a "high speed hub" that
	 * directly talks directly to low speed devices without a TT?
	 * It's all lies.  Lies, I tell you.
	 */
	if (usb_urb->dev->tt->hub == root_hub)
		return;

	if (qtd->urb->status != -EPIPE && qtd->urb->status != -EREMOTEIO) {
		chan->qh->tt_buffer_dirty = 1;
		if (usb_hub_clear_tt_buffer(usb_urb))
			/* Clear failed; let's hope things work anyway */
			chan->qh->tt_buffer_dirty = 0;
	}
}