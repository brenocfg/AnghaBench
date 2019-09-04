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
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct TYPE_2__ {int state; } ;
struct dwc3 {TYPE_1__ gadget; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_DEVICE_LTM_ENABLE 132 
#define  USB_DEVICE_REMOTE_WAKEUP 131 
#define  USB_DEVICE_TEST_MODE 130 
#define  USB_DEVICE_U1_ENABLE 129 
#define  USB_DEVICE_U2_ENABLE 128 
 int dwc3_ep0_handle_test (struct dwc3*,int,int,int) ; 
 int dwc3_ep0_handle_u1 (struct dwc3*,int,int) ; 
 int dwc3_ep0_handle_u2 (struct dwc3*,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_handle_device(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl, int set)
{
	enum usb_device_state	state;
	u32			wValue;
	u32			wIndex;
	int			ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);
	wIndex = le16_to_cpu(ctrl->wIndex);
	state = dwc->gadget.state;

	switch (wValue) {
	case USB_DEVICE_REMOTE_WAKEUP:
		break;
	/*
	 * 9.4.1 says only only for SS, in AddressState only for
	 * default control pipe
	 */
	case USB_DEVICE_U1_ENABLE:
		ret = dwc3_ep0_handle_u1(dwc, state, set);
		break;
	case USB_DEVICE_U2_ENABLE:
		ret = dwc3_ep0_handle_u2(dwc, state, set);
		break;
	case USB_DEVICE_LTM_ENABLE:
		ret = -EINVAL;
		break;
	case USB_DEVICE_TEST_MODE:
		ret = dwc3_ep0_handle_test(dwc, state, wIndex, set);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}