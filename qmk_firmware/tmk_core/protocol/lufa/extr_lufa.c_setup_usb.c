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

/* Variables and functions */
 int /*<<< orphan*/  USB_Device_EnableSOFEvents () ; 
 int /*<<< orphan*/  USB_Disable () ; 
 int /*<<< orphan*/  USB_Init () ; 
 int /*<<< orphan*/  print_set_sendchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendchar ; 

__attribute__((used)) static void setup_usb(void) {
    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}