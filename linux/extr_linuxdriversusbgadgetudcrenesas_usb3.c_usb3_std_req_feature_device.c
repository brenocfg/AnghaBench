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
typedef  int u16 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct renesas_usb3 {int test_mode; TYPE_1__ gadget; } ;

/* Variables and functions */
#define  USB_DEVICE_TEST_MODE 130 
#define  USB_DEVICE_U1_ENABLE 129 
#define  USB_DEVICE_U2_ENABLE 128 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_feature_u1_enable (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_feature_u2_enable (struct renesas_usb3*,int) ; 

__attribute__((used)) static bool usb3_std_req_feature_device(struct renesas_usb3 *usb3,
					struct usb_ctrlrequest *ctrl, bool set)
{
	bool stall = true;
	u16 w_value = le16_to_cpu(ctrl->wValue);

	switch (w_value) {
	case USB_DEVICE_TEST_MODE:
		if (!set)
			break;
		usb3->test_mode = le16_to_cpu(ctrl->wIndex) >> 8;
		stall = false;
		break;
	case USB_DEVICE_U1_ENABLE:
	case USB_DEVICE_U2_ENABLE:
		if (usb3->gadget.speed != USB_SPEED_SUPER)
			break;
		if (w_value == USB_DEVICE_U1_ENABLE)
			usb3_feature_u1_enable(usb3, set);
		if (w_value == USB_DEVICE_U2_ENABLE)
			usb3_feature_u2_enable(usb3, set);
		stall = false;
		break;
	default:
		break;
	}

	return stall;
}