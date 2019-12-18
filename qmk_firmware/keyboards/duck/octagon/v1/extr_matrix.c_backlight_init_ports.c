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

void backlight_init_ports(void)
{
    DDRB |= 0b00011111;  // PB0 (caps), PB1 (alpha), PB2 (extra), PB3 (modnum), PB4 (caps)
    DDRD |= 0b11010000;  // PD4, (rgb blue), PD6 (rgb red), PD7 (rgb green)
    DDRE |= 0b01000000;  // PE6 (frow)
}