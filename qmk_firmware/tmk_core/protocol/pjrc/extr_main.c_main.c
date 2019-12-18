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
 int /*<<< orphan*/  CPU_PRESCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_setup () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  pjrc_driver () ; 
 int /*<<< orphan*/  print_set_sendchar (int /*<<< orphan*/ ) ; 
 scalar_t__ remote_wakeup ; 
 int /*<<< orphan*/  sendchar ; 
 int /*<<< orphan*/  sleep_led_init () ; 
 scalar_t__ suspend ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 scalar_t__ suspend_wakeup_condition () ; 
 int /*<<< orphan*/  usb_configured () ; 
 int /*<<< orphan*/  usb_init () ; 
 int /*<<< orphan*/  usb_remote_wakeup () ; 

int main(void) {
    // set for 16 MHz clock
    CPU_PRESCALE(0);

    keyboard_setup();

    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) /* wait */
        ;

    print_set_sendchar(sendchar);

    keyboard_init();
    host_set_driver(pjrc_driver());
#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif
    while (1) {
        while (suspend) {
            suspend_power_down();
            if (remote_wakeup && suspend_wakeup_condition()) {
                usb_remote_wakeup();
            }
        }

        keyboard_task();
    }
}