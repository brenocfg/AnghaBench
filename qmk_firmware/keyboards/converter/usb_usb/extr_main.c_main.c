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
 int /*<<< orphan*/  LED_TX_INIT ; 
 int /*<<< orphan*/  LED_TX_ON ; 
 int /*<<< orphan*/  LUFA_setup () ; 
 int /*<<< orphan*/  USB_USBTask () ; 
 int /*<<< orphan*/  debug (char*) ; 
 int debug_enable ; 
 int debug_keyboard ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  lufa_driver ; 
 int /*<<< orphan*/  sei () ; 

int main(void)
{
    // LED for debug
    LED_TX_INIT;
    LED_TX_ON;

    debug_enable = true;
    debug_keyboard = true;

    host_set_driver(&lufa_driver);
    keyboard_init();

    LUFA_setup();

    /* NOTE: Don't insert time consuming job here.
     * It'll cause unclear initialization failure when DFU reset(worm start).
     */
    sei();

/* Some keyboards bootup quickly and cannot be initialized with this startup wait.
    // wait for startup of sendchar routine
    while (USB_DeviceState != DEVICE_STATE_Configured) ;
    if (debug_enable) {
        _delay_ms(1000);
    }
*/

    debug("init: done\n");

    for (;;) {
        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        // LUFA Task for control request
        USB_USBTask();
#endif
    }

    return 0;
}