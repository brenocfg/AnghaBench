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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_TCR0 ; 
 int /*<<< orphan*/  RTL8152_REQT_READ ; 
 int /*<<< orphan*/  RTL8152_REQ_GET_REGS ; 
 int /*<<< orphan*/  RTL_VER_01 ; 
 int /*<<< orphan*/  RTL_VER_02 ; 
 int /*<<< orphan*/  RTL_VER_03 ; 
 int /*<<< orphan*/  RTL_VER_04 ; 
 int /*<<< orphan*/  RTL_VER_05 ; 
 int /*<<< orphan*/  RTL_VER_06 ; 
 int /*<<< orphan*/  RTL_VER_07 ; 
 int /*<<< orphan*/  RTL_VER_08 ; 
 int /*<<< orphan*/  RTL_VER_09 ; 
 int /*<<< orphan*/  RTL_VER_UNKNOWN ; 
 int VERSION_MASK ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rtl_get_version(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	u32 ocp_data = 0;
	__le32 *tmp;
	u8 version;
	int ret;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return 0;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      PLA_TCR0, MCU_TYPE_PLA, tmp, sizeof(*tmp), 500);
	if (ret > 0)
		ocp_data = (__le32_to_cpu(*tmp) >> 16) & VERSION_MASK;

	kfree(tmp);

	switch (ocp_data) {
	case 0x4c00:
		version = RTL_VER_01;
		break;
	case 0x4c10:
		version = RTL_VER_02;
		break;
	case 0x5c00:
		version = RTL_VER_03;
		break;
	case 0x5c10:
		version = RTL_VER_04;
		break;
	case 0x5c20:
		version = RTL_VER_05;
		break;
	case 0x5c30:
		version = RTL_VER_06;
		break;
	case 0x4800:
		version = RTL_VER_07;
		break;
	case 0x6000:
		version = RTL_VER_08;
		break;
	case 0x6010:
		version = RTL_VER_09;
		break;
	default:
		version = RTL_VER_UNKNOWN;
		dev_info(&intf->dev, "Unknown version 0x%04x\n", ocp_data);
		break;
	}

	dev_dbg(&intf->dev, "Detected version 0x%04x\n", version);

	return version;
}