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
 int /*<<< orphan*/  QT_SET_GET_DEVICE ; 
 int ssu100_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ssu100_setdevice(struct usb_device *dev, u8 *data)
{
	u16 x = ((u16)(data[1] << 8) | (u16)(data[0]));

	return ssu100_control_msg(dev, QT_SET_GET_DEVICE, x, 0);
}