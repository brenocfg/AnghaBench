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
 int DDRC ; 
 int DDRD ; 
 int DDRE ; 
 int DDRF ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 
 int PORTF ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
    // (tied to Vcc for hardware convenience)
    //DDRB  &= ~(1<<4);  // set B(4) as input
    //PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins
    // set as input with internal pull-up enabled
    DDRB  &= ~(1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTB |=  (1<<4 | 1<<5 | 1<<6 | 1<<7);

    DDRC  &= ~(1<<7 | 1<<6);
    PORTC |=  (1<<7 | 1<<6);

    DDRD  &= ~(1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTD |=  (1<<4 | 1<<5 | 1<<6 | 1<<7);

    DDRE  &= ~(1<<6);
    PORTE |=  (1<<6);

    DDRF  &= ~(1<<0 | 1<<1 | 1<<4 | 1<<6 | 1<<7);
    PORTF |=  (1<<0 | 1<<1 | 1<<4 | 1<<6 | 1<<7);

    matrix_init_user();
}