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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int is_selfpowered; } ;
struct lpc32xx_udc {int dev_status; struct lpc32xx_ep* ep; TYPE_1__ gadget; } ;
struct lpc32xx_ep {int /*<<< orphan*/  hwep_num; int /*<<< orphan*/  is_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEL_EP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAT_SEL_EP (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EP_IN ; 
 int EP_SEL_ST ; 
 int NUM_ENDPOINTS ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_HALT ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int udc_protocol_cmd_r (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write_hwep (struct lpc32xx_udc*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int udc_get_status(struct lpc32xx_udc *udc, u16 reqtype, u16 wIndex)
{
	struct lpc32xx_ep *ep;
	u32 ep0buff = 0, tmp;

	switch (reqtype & USB_RECIP_MASK) {
	case USB_RECIP_INTERFACE:
		break; /* Not supported */

	case USB_RECIP_DEVICE:
		ep0buff = udc->gadget.is_selfpowered;
		if (udc->dev_status & (1 << USB_DEVICE_REMOTE_WAKEUP))
			ep0buff |= (1 << USB_DEVICE_REMOTE_WAKEUP);
		break;

	case USB_RECIP_ENDPOINT:
		tmp = wIndex & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[tmp];
		if ((tmp == 0) || (tmp >= NUM_ENDPOINTS))
			return -EOPNOTSUPP;

		if (wIndex & USB_DIR_IN) {
			if (!ep->is_in)
				return -EOPNOTSUPP; /* Something's wrong */
		} else if (ep->is_in)
			return -EOPNOTSUPP; /* Not an IN endpoint */

		/* Get status of the endpoint */
		udc_protocol_cmd_w(udc, CMD_SEL_EP(ep->hwep_num));
		tmp = udc_protocol_cmd_r(udc, DAT_SEL_EP(ep->hwep_num));

		if (tmp & EP_SEL_ST)
			ep0buff = (1 << USB_ENDPOINT_HALT);
		else
			ep0buff = 0;
		break;

	default:
		break;
	}

	/* Return data */
	udc_write_hwep(udc, EP_IN, &ep0buff, 2);

	return 0;
}