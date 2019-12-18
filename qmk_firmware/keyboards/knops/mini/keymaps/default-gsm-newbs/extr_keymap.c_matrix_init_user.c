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
 int DDRB ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 
 int /*<<< orphan*/  led_init_ports () ; 
 int /*<<< orphan*/  set_layer_led (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
	led_init_ports();

	PORTB |= (1 << 7);
	DDRB &= ~(1<<7);

	PORTD |= (1<<7);
	PORTC |= (1<<6);
	PORTC |= (1<<7);
	PORTD |= (1<<4);
	PORTE |= (1<<6);
	PORTB |= (1<<4);
	PORTD |= (1<<6);

	set_layer_led(0);
}