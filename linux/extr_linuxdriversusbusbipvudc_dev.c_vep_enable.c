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
struct vudc {int /*<<< orphan*/  lock; int /*<<< orphan*/  driver; } ;
struct vep {scalar_t__ wedged; scalar_t__ halted; int /*<<< orphan*/  type; struct usb_endpoint_descriptor const* desc; } ;
struct TYPE_2__ {scalar_t__ type_control; } ;
struct usb_ep {unsigned int maxpacket; TYPE_1__ caps; } ;
struct usb_endpoint_descriptor {scalar_t__ bDescriptorType; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 scalar_t__ USB_DT_ENDPOINT ; 
 struct vudc* ep_to_vudc (struct vep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vep* to_vep (struct usb_ep*) ; 
 unsigned int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int vep_enable(struct usb_ep *_ep,
		const struct usb_endpoint_descriptor *desc)
{
	struct vep	*ep;
	struct vudc	*udc;
	unsigned int	maxp;
	unsigned long	flags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);

	if (!_ep || !desc || ep->desc || _ep->caps.type_control
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		return -EINVAL;

	if (!udc->driver)
		return -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);

	maxp = usb_endpoint_maxp(desc);
	_ep->maxpacket = maxp;
	ep->desc = desc;
	ep->type = usb_endpoint_type(desc);
	ep->halted = ep->wedged = 0;

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}