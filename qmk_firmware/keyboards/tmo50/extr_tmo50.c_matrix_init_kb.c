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
 int PB0 ; 
 int PB1 ; 
 int PB2 ; 
 int PB3 ; 
 int PORTB ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

  DDRB |= (1 << PB0); //init B0
  PORTB &= ~(1 << PB0); //turn on B0
  DDRB |= (1 << PB1);
  PORTB |= (1<<PB1); //turn off B1
  DDRB |= (1 << PB2);
  PORTB |= (1<<PB2);
  DDRB |= (1 << PB3);
  PORTB |= (1<<PB3);

	matrix_init_user();
}