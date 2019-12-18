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
 int DDRC ; 
 scalar_t__ MCUSR ; 
 int PCICR ; 
 int PCMSK1 ; 
 int PORTC ; 
 int /*<<< orphan*/  WDTO_60MS ; 
 int /*<<< orphan*/  WD_OFF ; 
 int /*<<< orphan*/  WD_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  clock_div_1 ; 
 int /*<<< orphan*/  clock_prescale_set (int /*<<< orphan*/ ) ; 
 scalar_t__ console () ; 
 int /*<<< orphan*/  disable_vusb () ; 
 scalar_t__ host_get_driver () ; 
 int /*<<< orphan*/  host_set_driver (scalar_t__) ; 
 int /*<<< orphan*/  insomniac ; 
 int /*<<< orphan*/  iwrap_call () ; 
 int /*<<< orphan*/  iwrap_check_connection () ; 
 scalar_t__ iwrap_driver () ; 
 int /*<<< orphan*/  iwrap_init () ; 
 int /*<<< orphan*/  iwrap_sleep () ; 
 int /*<<< orphan*/  keyboard_init () ; 
 int /*<<< orphan*/  keyboard_task () ; 
 int /*<<< orphan*/  last_timer ; 
 scalar_t__ matrix_is_modified () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int sleeping ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  uart_init (int) ; 
 int /*<<< orphan*/  usbPoll () ; 
 scalar_t__ vusb_driver () ; 
 int /*<<< orphan*/  vusb_transfer_keyboard () ; 

int main(void) {
    MCUSR = 0;
    clock_prescale_set(clock_div_1);
    WD_SET(WD_OFF);

    // power saving: the result is worse than nothing... why?
    // pullup_pins();
    // set_prr();

#ifdef PROTOCOL_VUSB
    disable_vusb();
#endif
    uart_init(115200);
    keyboard_init();
    print("\nSend BREAK for UART Console Commands.\n");

    // TODO: move to iWRAP/suart file
    print("suart init\n");
    // suart init
    // PC4: Tx Output IDLE(Hi)
    PORTC |= (1 << 4);
    DDRC |= (1 << 4);
    // PC5: Rx Input(pull-up)
    PORTC |= (1 << 5);
    DDRC &= ~(1 << 5);
    // suart receive interrut(PC5/PCINT13)
    PCMSK1 = 0b00100000;
    PCICR  = 0b00000010;

    host_set_driver(iwrap_driver());

    print("iwrap_init()\n");
    iwrap_init();
    iwrap_call();

    last_timer = timer_read();
    while (true) {
#ifdef PROTOCOL_VUSB
        if (host_get_driver() == vusb_driver()) usbPoll();
#endif
        keyboard_task();
#ifdef PROTOCOL_VUSB
        if (host_get_driver() == vusb_driver()) vusb_transfer_keyboard();
#endif
        // TODO: depricated
        if (matrix_is_modified() || console()) {
            last_timer = timer_read();
            sleeping   = false;
        } else if (!sleeping && timer_elapsed(last_timer) > 4000) {
            sleeping = true;
            iwrap_check_connection();
        }

        // TODO: suspend.h
        if (host_get_driver() == iwrap_driver()) {
            if (sleeping && !insomniac) {
                _delay_ms(1);  // wait for UART to send
                iwrap_sleep();
                sleep(WDTO_60MS);
            }
        }
    }
}