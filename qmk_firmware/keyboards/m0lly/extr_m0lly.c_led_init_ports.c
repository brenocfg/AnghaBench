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
 int PORTB ; 

void led_init_ports(void) {
	DDRD |= (1<<2) | (1<<3) | (1<<4); // OUT
	DDRB |= (1<<7); // OUT
	PORTB |= (1<<7);
}