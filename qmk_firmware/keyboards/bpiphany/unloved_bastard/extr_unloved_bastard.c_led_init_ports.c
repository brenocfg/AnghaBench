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
 int PORTB ; 
 int PORTC ; 

void led_init_ports(void) {
    DDRB |= (1<<7);
    DDRC |= (1<<5);
    DDRC |= (1<<6);

    PORTB |= (1<<7);
    PORTC |= (1<<5);
    PORTC |= (1<<6);
}