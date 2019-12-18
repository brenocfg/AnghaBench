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

__attribute__((used)) static void unselect_cols(void) {
    DDRB  |= (1<<5) | (1<<6) | (1<<0) | (1<<7) | (1<<4); // OUT
    PORTB &= ~((1<<5) | (1<<6) | (1<<0) |  (1<<7) | (1<<4)); // LO

    DDRD  |= (1<<4) | (1<<6) | (1<<7); // OUT
    PORTD &= ~((1<<4) | (1<<6) | (1<<7)); // LO

    DDRE  |= (1<<6); // OUT
    PORTE &= ~((1<<6)); // LO

    DDRF  |= (1<<0) | (1<<1); // OUT
    PORTF &= ~((1<<0) | (1<<1)); // LO

    DDRC  |= (1<<7) | (1<<6); // OUT
    PORTC &= ~((1<<7) | (1<<6)); // LO
}