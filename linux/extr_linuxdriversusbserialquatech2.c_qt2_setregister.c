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
typedef  int u8 ;
typedef  int u16 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT2_USB_TIMEOUT ; 
 int /*<<< orphan*/  QT_SET_GET_REGISTER ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qt2_setregister(struct usb_device *dev,
				  u8 uart, u8 reg, u16 data)
{
	u16 value = (data << 8) | reg;

	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			       QT_SET_GET_REGISTER, 0x40, value, uart,
			       NULL, 0, QT2_USB_TIMEOUT);
}