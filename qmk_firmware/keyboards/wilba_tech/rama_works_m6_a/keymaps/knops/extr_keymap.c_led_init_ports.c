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
 int DDRF ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTF ; 

void led_init_ports()
{
    // Switch #1
    DDRD |= (1 << 6);
    PORTD &= ~(1 << 6);

    // Switch #2
    DDRB |= (1 << 6);
    PORTB &= ~(1 << 6);

    // Switch #3
    DDRF |= (1 << 5);
    PORTF &= ~(1 << 5);

    // Switch #4
    DDRB |= (1 << 4);
    PORTB &= ~(1 << 4);

    // Switch #5
    DDRC |= (1 << 7);
    PORTC &= ~(1 << 7);

    // Switch #6
    DDRF |= (1 << 7);
    PORTF &= ~(1 << 7);
}