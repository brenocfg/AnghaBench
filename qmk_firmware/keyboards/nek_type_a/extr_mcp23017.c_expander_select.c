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
 int /*<<< orphan*/  EXPANDER_PAUSE ; 
 int /*<<< orphan*/  EXPANDER_REG_IODIRA ; 
 int /*<<< orphan*/  EXPANDER_REG_IODIRB ; 
 int /*<<< orphan*/  EXPANDER_REG_OLATA ; 
 int /*<<< orphan*/  EXPANDER_REG_OLATB ; 
 int bit_for_pin (int) ; 
 int /*<<< orphan*/  expander_write (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  wait_us (int /*<<< orphan*/ ) ; 

void expander_select(uint8_t pin) {
    const uint8_t mask = 0xff & ~(1 << bit_for_pin(pin));
    if (pin < 8) {
        expander_write(EXPANDER_REG_IODIRA, mask);
        expander_write(EXPANDER_REG_OLATA, mask);
    } else {
        expander_write(EXPANDER_REG_IODIRB, mask);
        expander_write(EXPANDER_REG_OLATB, mask);
    }
    wait_us(EXPANDER_PAUSE);
}