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
 int PORTD ; 
 int /*<<< orphan*/  print (char*) ; 

void backlight_init_ports(void) {
    print("init_backlight_pin()\n");
    // Set our LED pins as output
    DDRD |= (1<<0); // Esc
    DDRD |= (1<<4); // Page Up
    DDRD |= (1<<1); // Arrows

    // Set our LED pins low
    PORTD &= ~(1<<0); // Esc
    PORTD &= ~(1<<4); // Page Up
    PORTD &= ~(1<<1); // Arrows
}