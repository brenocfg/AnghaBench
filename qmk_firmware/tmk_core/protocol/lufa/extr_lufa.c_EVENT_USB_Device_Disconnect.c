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
 int USB_IsInitialized ; 
 int /*<<< orphan*/  print (char*) ; 

void EVENT_USB_Device_Disconnect(void) {
    print("[D]");
    /* For battery powered device */
    USB_IsInitialized = false;
    /* TODO: This doesn't work. After several plug in/outs can not be enumerated.
        if (USB_IsInitialized) {
            USB_Disable();  // Disable all interrupts
        USB_Controller_Enable();
            USB_INT_Enable(USB_INT_VBUSTI);
        }
    */
}