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
 int DDRD ; 
 int DDRF ; 
 int PORTD ; 
 int PORTF ; 

void led_init(void) {
	DDRD  |= (1<<1); // Pin to green, set as output
	PORTD |= (1<<1); // Turn it off
	DDRF  |= (1<<4) | (1<<5); // Pins to red and blue, set as output
	PORTF |= (1<<4) | (1<<5); // Turn them off
}