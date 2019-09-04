#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device {int dummy; } ;
typedef  int s32 ;
struct TYPE_3__ {int bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HSO_INFO_CRC_BUG ; 
 int HSO_INTF_BULK ; 
 int HSO_PORT_APP ; 
 int HSO_PORT_APP2 ; 
 int HSO_PORT_CONTROL ; 
 int HSO_PORT_DIAG ; 
 int HSO_PORT_GPS ; 
 int HSO_PORT_GPS_CONTROL ; 
 int HSO_PORT_MODEM ; 
 int HSO_PORT_MSD ; 
 int HSO_PORT_NETWORK ; 
 int HSO_PORT_PCSC ; 
 int HSO_PORT_VOICE ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_get_config_data(struct usb_interface *interface)
{
	struct usb_device *usbdev = interface_to_usbdev(interface);
	u8 *config_data = kmalloc(17, GFP_KERNEL);
	u32 if_num = interface->cur_altsetting->desc.bInterfaceNumber;
	s32 result;

	if (!config_data)
		return -ENOMEM;
	if (usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			    0x86, 0xC0, 0, 0, config_data, 17,
			    USB_CTRL_SET_TIMEOUT) != 0x11) {
		kfree(config_data);
		return -EIO;
	}

	/* check if we have a valid interface */
	if (if_num > 16) {
		kfree(config_data);
		return -EINVAL;
	}

	switch (config_data[if_num]) {
	case 0x0:
		result = 0;
		break;
	case 0x1:
		result = HSO_PORT_DIAG;
		break;
	case 0x2:
		result = HSO_PORT_GPS;
		break;
	case 0x3:
		result = HSO_PORT_GPS_CONTROL;
		break;
	case 0x4:
		result = HSO_PORT_APP;
		break;
	case 0x5:
		result = HSO_PORT_APP2;
		break;
	case 0x6:
		result = HSO_PORT_CONTROL;
		break;
	case 0x7:
		result = HSO_PORT_NETWORK;
		break;
	case 0x8:
		result = HSO_PORT_MODEM;
		break;
	case 0x9:
		result = HSO_PORT_MSD;
		break;
	case 0xa:
		result = HSO_PORT_PCSC;
		break;
	case 0xb:
		result = HSO_PORT_VOICE;
		break;
	default:
		result = 0;
	}

	if (result)
		result |= HSO_INTF_BULK;

	if (config_data[16] & 0x1)
		result |= HSO_INFO_CRC_BUG;

	kfree(config_data);
	return result;
}