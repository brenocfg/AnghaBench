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
struct usb_function_instance {int dummy; } ;

/* Variables and functions */
 int usb_composite_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbg_driver ; 

__attribute__((used)) static int usbg_attach(struct usb_function_instance *f)
{
	return usb_composite_probe(&usbg_driver);
}