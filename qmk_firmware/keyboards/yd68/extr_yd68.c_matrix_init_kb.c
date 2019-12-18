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
 int DDRD ; 
 int DDRE ; 
 int PORTB ; 
 int PORTD ; 
 int PORTE ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	//Capslock LED Output Low
	DDRD |= (1<<4);
    PORTD &= ~(1<<4);
	
	//Backlight LEDs Output Low
	DDRD |= (1<<6);
    PORTD &= ~(1<<6);
	
	//RGB power output low
	DDRE |= (1<<2);
    PORTE &= ~(1<<2);
	
	//Bluetooth power output high
	DDRB |= (1<<2);
    PORTB |= (1<<2);
	
	//RGB data output low
	DDRB |= (1<<3);
	PORTB &= ~(1<<3);
	
	matrix_init_user();
}