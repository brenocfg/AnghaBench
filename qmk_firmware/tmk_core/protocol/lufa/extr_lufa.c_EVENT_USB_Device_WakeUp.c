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
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int /*<<< orphan*/  led_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  sleep_led_disable () ; 
 int /*<<< orphan*/  suspend_wakeup_init () ; 

void EVENT_USB_Device_WakeUp() {
    print("[W]");
    suspend_wakeup_init();

#ifdef SLEEP_LED_ENABLE
    sleep_led_disable();
    // NOTE: converters may not accept this
    led_set(host_keyboard_leds());
#endif
}