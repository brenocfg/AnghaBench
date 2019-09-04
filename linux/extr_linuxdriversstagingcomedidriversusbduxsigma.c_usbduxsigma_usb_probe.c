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
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int comedi_usb_auto_config (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbduxsigma_driver ; 

__attribute__((used)) static int usbduxsigma_usb_probe(struct usb_interface *intf,
				 const struct usb_device_id *id)
{
	return comedi_usb_auto_config(intf, &usbduxsigma_driver, 0);
}