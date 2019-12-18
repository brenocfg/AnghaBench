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
struct usb_module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_SUSPEND_EVENT () ; 
 int /*<<< orphan*/  UDD_STATE_SUSPEND ; 
 int /*<<< orphan*/  USB_DEVICE_CALLBACK_SUSPEND ; 
 int /*<<< orphan*/  USB_DEVICE_CALLBACK_WAKEUP ; 
 int /*<<< orphan*/  udd_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_disable_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_enable_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _usb_on_suspend(struct usb_module *module_inst, void *pointer) {
    usb_device_disable_callback(&usb_device, USB_DEVICE_CALLBACK_SUSPEND);
    usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_WAKEUP);
    udd_sleep_mode(UDD_STATE_SUSPEND);
#ifdef UDC_SUSPEND_EVENT
    UDC_SUSPEND_EVENT();
#endif
}