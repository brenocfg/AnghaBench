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
 int BL_BLUE ; 
 int BL_GREEN ; 
 int BL_RED ; 
 int DDRB ; 
 int ICR1 ; 
 int TCCR1A ; 
 int TCCR1B ; 

void backlight_init_ports(void)
{
	// Set B5, B6, and B7 as output
	DDRB |= (1<<7)|(1<<6)|(1<<5);

	// Setup PWM
	ICR1 = 0xFFFF;
	TCCR1A = 0b10101010;
	TCCR1B = 0b00011001;

	BL_RED = 0xFFFF;
	BL_GREEN = 0xFFFF;
	BL_BLUE = 0xFFFF;
}