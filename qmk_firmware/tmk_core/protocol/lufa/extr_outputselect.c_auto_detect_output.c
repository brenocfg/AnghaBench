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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_Configured ; 
 int /*<<< orphan*/  OUTPUT_BLUETOOTH ; 
 int /*<<< orphan*/  OUTPUT_NONE ; 
 int /*<<< orphan*/  OUTPUT_USB ; 
 scalar_t__ USB_DeviceState ; 
 scalar_t__ adafruit_ble_is_connected () ; 

uint8_t auto_detect_output(void) {
    if (USB_DeviceState == DEVICE_STATE_Configured) {
        return OUTPUT_USB;
    }

#ifdef MODULE_ADAFRUIT_BLE
    if (adafruit_ble_is_connected()) {
        return OUTPUT_BLUETOOTH;
    }
#endif

#ifdef BLUETOOTH_ENABLE
    return OUTPUT_BLUETOOTH;  // should check if BT is connected here
#endif

    return OUTPUT_NONE;
}