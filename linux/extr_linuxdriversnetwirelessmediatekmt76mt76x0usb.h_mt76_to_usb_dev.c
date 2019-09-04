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
struct usb_device {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct usb_device *mt76_to_usb_dev(struct mt76_dev *mt76)
{
	return interface_to_usbdev(to_usb_interface(mt76->dev));
}