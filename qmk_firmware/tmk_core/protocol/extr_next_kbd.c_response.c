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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ NEXT_KBD_READ ; 
 int NEXT_KBD_TIMING ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  reset () ; 
 int /*<<< orphan*/  sei () ; 

__attribute__((used)) static inline uint32_t response(void) {
    cli();

    // try a 5ms read; this should be called after the query method has
    // been run so if a key is pressed we should get a response within
    // 5ms; if not then send a reset and exit
    uint8_t  i             = 0;
    uint32_t data          = 0;
    uint16_t reset_timeout = 50000;
    while (NEXT_KBD_READ && reset_timeout) {
        asm("");
        _delay_us(1);
        reset_timeout--;
    }
    if (!reset_timeout) {
        reset();
        sei();
        return 0;
    }
    _delay_us(NEXT_KBD_TIMING / 2);
    for (; i < 22; i++) {
        if (NEXT_KBD_READ) {
            data |= ((uint32_t)1 << i);
            /* Note:
             * My testing with the ATmega32u4 showed that there might
             * something wrong with the timing here; by the end of the
             * second data byte some of the modifiers can get bumped out
             * to the next bit over if we just cycle through the data
             * based on the expected interval.  There is a bit (i = 10)
             * in the middle of the data that is always on followed by
             * one that is always off - so we'll use that to reset our
             * timing in case we've gotten ahead of the keyboard;
             */
            if (i == 10) {
                i++;
                while (NEXT_KBD_READ)
                    ;
                _delay_us(NEXT_KBD_TIMING / 2);
            }
        } else {
            /* redundant - but I don't want to remove if it might screw
             * up the timing
             */
            data |= ((uint32_t)0 << i);
        }
        _delay_us(NEXT_KBD_TIMING);
    }

    sei();

    return data;
}