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
 int /*<<< orphan*/  UDC_RESUME_EVENT () ; 
 int /*<<< orphan*/  UDD_STATE_IDLE ; 
 int /*<<< orphan*/  USB_DEVICE_CALLBACK_LPMSUSP ; 
 int /*<<< orphan*/  USB_DEVICE_CALLBACK_SUSPEND ; 
 int /*<<< orphan*/  USB_DEVICE_CALLBACK_WAKEUP ; 
 int /*<<< orphan*/  _usb_device_lpm_suspend ; 
 int /*<<< orphan*/  udd_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udd_wait_clock_ready () ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_disable_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_enable_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_register_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _usb_on_wakeup(struct usb_module *module_inst, void *pointer) {
    udd_wait_clock_ready();

    usb_device_disable_callback(&usb_device, USB_DEVICE_CALLBACK_WAKEUP);
    usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_SUSPEND);
#ifdef USB_DEVICE_LPM_SUPPORT
    usb_device_register_callback(&usb_device, USB_DEVICE_CALLBACK_LPMSUSP, _usb_device_lpm_suspend);
    usb_device_enable_callback(&usb_device, USB_DEVICE_CALLBACK_LPMSUSP);
#endif
    udd_sleep_mode(UDD_STATE_IDLE);
#ifdef UDC_RESUME_EVENT
    UDC_RESUME_EVENT();
#endif
}