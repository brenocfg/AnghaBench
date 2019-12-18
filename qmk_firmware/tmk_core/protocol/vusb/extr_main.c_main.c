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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int CLKPR ; 
 int /*<<< orphan*/  UART_BAUD_RATE ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initForUsbConnectivity () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_setup () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  rgblight_task () ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  uart_init (int /*<<< orphan*/ ) ; 
 scalar_t__ usbConfiguration ; 
 scalar_t__ usbInterruptIsReady () ; 
 int /*<<< orphan*/  usbPoll () ; 
 scalar_t__ usbSofCount ; 
 int /*<<< orphan*/  vusb_driver () ; 
 int /*<<< orphan*/  vusb_transfer_keyboard () ; 

int main(void) {
    bool suspended = false;
#if USB_COUNT_SOF
    uint16_t last_timer = timer_read();
#endif

#ifdef CLKPR
    // avoid unintentional changes of clock frequency in devices that have a
    // clock prescaler
    CLKPR = 0x80, CLKPR = 0;
#endif
#ifndef NO_UART
    uart_init(UART_BAUD_RATE);
#endif
    keyboard_setup();

    keyboard_init();
    host_set_driver(vusb_driver());

    debug("initForUsbConnectivity()\n");
    initForUsbConnectivity();

    debug("main loop\n");
    while (1) {
#if USB_COUNT_SOF
        if (usbSofCount != 0) {
            suspended   = false;
            usbSofCount = 0;
            last_timer  = timer_read();
        } else {
            // Suspend when no SOF in 3ms-10ms(7.1.7.4 Suspending of USB1.1)
            if (timer_elapsed(last_timer) > 5) {
                suspended = true;
                /*
                                uart_putchar('S');
                                _delay_ms(1);
                                cli();
                                set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                                sleep_enable();
                                sleep_bod_disable();
                                sei();
                                sleep_cpu();
                                sleep_disable();
                                _delay_ms(10);
                                uart_putchar('W');
                */
            }
        }
#endif
        if (!suspended) {
            usbPoll();

            // TODO: configuration process is incosistent. it sometime fails.
            // To prevent failing to configure NOT scan keyboard during configuration
            if (usbConfiguration && usbInterruptIsReady()) {
                keyboard_task();

#if defined(RGBLIGHT_ANIMATIONS) && defined(RGBLIGHT_ENABLE)
                rgblight_task();
#endif
            }
            vusb_transfer_keyboard();
        }
    }
}