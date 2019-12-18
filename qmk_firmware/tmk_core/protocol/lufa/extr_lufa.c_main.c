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
 int /*<<< orphan*/  CDC_Device_USBTask (int /*<<< orphan*/ *) ; 
 scalar_t__ DEVICE_STATE_Configured ; 
 scalar_t__ DEVICE_STATE_Suspended ; 
 int /*<<< orphan*/  MIDI_Device_USBTask (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_DeviceState ; 
 scalar_t__ USB_Device_RemoteWakeupEnabled ; 
 int /*<<< orphan*/  USB_Device_SendRemoteWakeup () ; 
 int /*<<< orphan*/  USB_MIDI_Interface ; 
 int /*<<< orphan*/  USB_USBTask () ; 
 int /*<<< orphan*/  adafruit_ble_task () ; 
 int /*<<< orphan*/  cdc_device ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_setup () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  lufa_driver ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  raw_hid_task () ; 
 int /*<<< orphan*/  rgblight_task () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  serial_init () ; 
 int /*<<< orphan*/  setup_mcu () ; 
 int /*<<< orphan*/  setup_midi () ; 
 int /*<<< orphan*/  setup_usb () ; 
 int /*<<< orphan*/  sleep_led_init () ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 scalar_t__ suspend_wakeup_condition () ; 
 int /*<<< orphan*/  virtser_init () ; 
 int /*<<< orphan*/  virtser_task () ; 

int main(void) {
#ifdef MIDI_ENABLE
    setup_midi();
#endif

    setup_mcu();
    keyboard_setup();
    setup_usb();
    sei();

#if defined(MODULE_ADAFRUIT_EZKEY) || defined(MODULE_RN42)
    serial_init();
#endif

    /* wait for USB startup & debug output */

#ifdef WAIT_FOR_USB
    while (USB_DeviceState != DEVICE_STATE_Configured) {
#    if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#    else
        USB_USBTask();
#    endif
    }
    print("USB configured.\n");
#else
    USB_USBTask();
#endif
    /* init modules */
    keyboard_init();
    host_set_driver(&lufa_driver);
#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

#ifdef VIRTSER_ENABLE
    virtser_init();
#endif

    print("Keyboard start.\n");
    while (1) {
#if !defined(NO_USB_STARTUP_CHECK)
        while (USB_DeviceState == DEVICE_STATE_Suspended) {
            print("[s]");
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                USB_Device_SendRemoteWakeup();
            }
        }
#endif

        keyboard_task();

#ifdef MIDI_ENABLE
        MIDI_Device_USBTask(&USB_MIDI_Interface);
#endif

#if defined(RGBLIGHT_ANIMATIONS) && defined(RGBLIGHT_ENABLE)
        rgblight_task();
#endif

#ifdef MODULE_ADAFRUIT_BLE
        adafruit_ble_task();
#endif

#ifdef VIRTSER_ENABLE
        virtser_task();
        CDC_Device_USBTask(&cdc_device);
#endif

#ifdef RAW_ENABLE
        raw_hid_task();
#endif

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif
    }
}