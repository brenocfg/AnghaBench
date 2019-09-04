#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_5__ {int b_hnp_enable; int a_hnp_support; int a_alt_hnp_support; } ;
struct vudc {unsigned int address; int devstatus; TYPE_4__* ep; TYPE_1__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct vep {int halted; int /*<<< orphan*/  wedged; TYPE_2__ ep; } ;
struct usb_ctrlrequest {int bRequest; int /*<<< orphan*/  bRequestType; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/  actual_length; scalar_t__ transfer_buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_3__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INREQUEST ; 
 int /*<<< orphan*/  DEV_REQUEST ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EP_INREQUEST ; 
 int /*<<< orphan*/  EP_REQUEST ; 
 int /*<<< orphan*/  INTF_INREQUEST ; 
#define  USB_DEVICE_A_ALT_HNP_SUPPORT 138 
#define  USB_DEVICE_A_HNP_SUPPORT 137 
#define  USB_DEVICE_B_HNP_ENABLE 136 
#define  USB_DEVICE_LTM_ENABLE 135 
#define  USB_DEVICE_REMOTE_WAKEUP 134 
#define  USB_DEVICE_U1_ENABLE 133 
#define  USB_DEVICE_U2_ENABLE 132 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
#define  USB_REQ_SET_FEATURE 128 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  u32 ; 
 struct vep* vudc_find_endpoint (struct vudc*,unsigned int) ; 

__attribute__((used)) static int handle_control_request(struct vudc *udc, struct urb *urb,
				  struct usb_ctrlrequest *setup,
				  int *status)
{
	struct vep	*ep2;
	int		ret_val = 1;
	unsigned int	w_index;
	unsigned int	w_value;

	w_index = le16_to_cpu(setup->wIndex);
	w_value = le16_to_cpu(setup->wValue);
	switch (setup->bRequest) {
	case USB_REQ_SET_ADDRESS:
		if (setup->bRequestType != DEV_REQUEST)
			break;
		udc->address = w_value;
		ret_val = 0;
		*status = 0;
		break;
	case USB_REQ_SET_FEATURE:
		if (setup->bRequestType == DEV_REQUEST) {
			ret_val = 0;
			switch (w_value) {
			case USB_DEVICE_REMOTE_WAKEUP:
				break;
			case USB_DEVICE_B_HNP_ENABLE:
				udc->gadget.b_hnp_enable = 1;
				break;
			case USB_DEVICE_A_HNP_SUPPORT:
				udc->gadget.a_hnp_support = 1;
				break;
			case USB_DEVICE_A_ALT_HNP_SUPPORT:
				udc->gadget.a_alt_hnp_support = 1;
				break;
			default:
				ret_val = -EOPNOTSUPP;
			}
			if (ret_val == 0) {
				udc->devstatus |= (1 << w_value);
				*status = 0;
			}
		} else if (setup->bRequestType == EP_REQUEST) {
			/* endpoint halt */
			ep2 = vudc_find_endpoint(udc, w_index);
			if (!ep2 || ep2->ep.name == udc->ep[0].ep.name) {
				ret_val = -EOPNOTSUPP;
				break;
			}
			ep2->halted = 1;
			ret_val = 0;
			*status = 0;
		}
		break;
	case USB_REQ_CLEAR_FEATURE:
		if (setup->bRequestType == DEV_REQUEST) {
			ret_val = 0;
			switch (w_value) {
			case USB_DEVICE_REMOTE_WAKEUP:
				w_value = USB_DEVICE_REMOTE_WAKEUP;
				break;

			case USB_DEVICE_U1_ENABLE:
			case USB_DEVICE_U2_ENABLE:
			case USB_DEVICE_LTM_ENABLE:
				ret_val = -EOPNOTSUPP;
				break;
			default:
				ret_val = -EOPNOTSUPP;
				break;
			}
			if (ret_val == 0) {
				udc->devstatus &= ~(1 << w_value);
				*status = 0;
			}
		} else if (setup->bRequestType == EP_REQUEST) {
			/* endpoint halt */
			ep2 = vudc_find_endpoint(udc, w_index);
			if (!ep2) {
				ret_val = -EOPNOTSUPP;
				break;
			}
			if (!ep2->wedged)
				ep2->halted = 0;
			ret_val = 0;
			*status = 0;
		}
		break;
	case USB_REQ_GET_STATUS:
		if (setup->bRequestType == DEV_INREQUEST
				|| setup->bRequestType == INTF_INREQUEST
				|| setup->bRequestType == EP_INREQUEST) {
			char *buf;
			/*
			 * device: remote wakeup, selfpowered
			 * interface: nothing
			 * endpoint: halt
			 */
			buf = (char *)urb->transfer_buffer;
			if (urb->transfer_buffer_length > 0) {
				if (setup->bRequestType == EP_INREQUEST) {
					ep2 = vudc_find_endpoint(udc, w_index);
					if (!ep2) {
						ret_val = -EOPNOTSUPP;
						break;
					}
					buf[0] = ep2->halted;
				} else if (setup->bRequestType ==
					   DEV_INREQUEST) {
					buf[0] = (u8)udc->devstatus;
				} else
					buf[0] = 0;
			}
			if (urb->transfer_buffer_length > 1)
				buf[1] = 0;
			urb->actual_length = min_t(u32, 2,
				urb->transfer_buffer_length);
			ret_val = 0;
			*status = 0;
		}
		break;
	}
	return ret_val;
}