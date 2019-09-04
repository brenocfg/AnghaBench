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
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_usb_device_detached (struct usb_interface*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_usb_remove(struct usb_interface *interface)
{
	usb_put_dev(interface_to_usbdev(interface));
	ath6kl_usb_device_detached(interface);
}