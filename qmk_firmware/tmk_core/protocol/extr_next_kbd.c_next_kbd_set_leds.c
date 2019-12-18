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
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  out_hi () ; 
 int /*<<< orphan*/  out_hi_delay (int) ; 
 int /*<<< orphan*/  out_lo_delay (int) ; 
 int /*<<< orphan*/  sei () ; 

void next_kbd_set_leds(bool left, bool right) {
    cli();
    out_lo_delay(9);

    out_hi_delay(3);
    out_lo_delay(1);

    if (left) {
        out_hi_delay(1);
    } else {
        out_lo_delay(1);
    }

    if (right) {
        out_hi_delay(1);
    } else {
        out_lo_delay(1);
    }

    out_lo_delay(7);
    out_hi();
    sei();
}