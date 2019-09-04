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
struct usb_hcd {int dummy; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_get_hcd (struct usb_hcd*) ; 

__attribute__((used)) static inline
struct usb_hcd *usb_hcd_get_by_usb_dev(struct usb_device *usb_dev)
{
	struct usb_hcd *usb_hcd;
	usb_hcd = bus_to_hcd(usb_dev->bus);
	return usb_get_hcd(usb_hcd);
}