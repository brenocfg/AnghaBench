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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_Configured ; 
 scalar_t__ DEVICE_STATE_Suspended ; 
 int /*<<< orphan*/  SetupHardware () ; 
 scalar_t__ USB_DeviceState ; 
 scalar_t__ USB_Device_RemoteWakeupEnabled ; 
 int /*<<< orphan*/  USB_Device_SendRemoteWakeup () ; 
 int /*<<< orphan*/  USB_USBTask () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  matrix_power_down () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  rn42_init () ; 
 scalar_t__ rn42_rts () ; 
 int /*<<< orphan*/  rn42_task () ; 
 int /*<<< orphan*/  rn42_task_init () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  sleep_led_init () ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 scalar_t__ suspend_wakeup_condition () ; 
 int /*<<< orphan*/  wait_ms (int) ; 

int main(void)
{
    SetupHardware();
    sei();

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 255;  // timeout when USB is not available(Bluetooth)
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured) {
        wait_ms(4);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif
    }
    print("\nUSB init\n");

    rn42_init();
    rn42_task_init();
    print("RN-42 init\n");

    /* init modules */
    keyboard_init();

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start\n");
    while (1) {
        while (rn42_rts() && // RN42 is off
                USB_DeviceState == DEVICE_STATE_Suspended) {
            print("[s]");
            matrix_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                    USB_Device_SendRemoteWakeup();
            }
        }

        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif

        rn42_task();
    }
}