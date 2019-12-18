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
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
    // // green led on
    // DDRD |= (1<<5);
    // PORTD &= ~(1<<5);

    // // orange led on
    // DDRB |= (1<<0);
    // PORTB &= ~(1<<0);

	matrix_init_user();
}