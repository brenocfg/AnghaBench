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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  apa102_send_byte (int) ; 

void apa102_end_frame(uint16_t leds) {
    // This function has been taken from: https://github.com/pololu/apa102-arduino/blob/master/APA102.h
    // and adapted. The code is MIT licensed. I think thats compatible?

    // We need to send some more bytes to ensure that all the LEDs in the
    // chain see their new color and start displaying it.
    //
    // The data stream seen by the last LED in the chain will be delayed by
    // (count - 1) clock edges, because each LED before it inverts the clock
    // line and delays the data by one clock edge.  Therefore, to make sure
    // the last LED actually receives the data we wrote, the number of extra
    // edges we send at the end of the frame must be at least (count - 1).
    // For the APA102C, that is sufficient.
    //
    // The SK9822 only updates after it sees 32 zero bits followed by one more
    // rising edge.  To avoid having the update time depend on the color of
    // the last LED, we send a dummy 0xFF byte.  (Unfortunately, this means
    // that partial updates of the beginning of an LED strip are not possible;
    // the LED after the last one you are trying to update will be black.)
    // After that, to ensure that the last LED in the chain sees 32 zero bits
    // and a rising edge, we need to send at least 65 + (count - 1) edges.  It
    // is sufficent and simpler to just send (5 + count/16) bytes of zeros.
    //
    // We are ignoring the specification for the end frame in the APA102/SK9822
    // datasheets because it does not actually ensure that all the LEDs will
    // start displaying their new colors right away.

    apa102_send_byte(0xFF);
    for (uint16_t i = 0; i < 5 + leds / 16; i++) {
        apa102_send_byte(0);
    }
}