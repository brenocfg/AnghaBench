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
 int /*<<< orphan*/  USB_IsInitialized ; 
 int /*<<< orphan*/  print (char*) ; 

void EVENT_USB_Device_Connect(void) {
    print("[C]");
    /* For battery powered device */
    if (!USB_IsInitialized) {
        USB_Disable();
        USB_Init();
        USB_Device_EnableSOFEvents();
    }
}