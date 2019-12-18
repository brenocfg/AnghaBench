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
 int DDRC ; 
 int OCR4C ; 
 int TC4H ; 
 int TCCR4A ; 
 int TCCR4B ; 

void backlight_init_ports(void) {
    // Set C7 to output
    DDRC |= (1<<7);

    // Initialize the timer
    TC4H = 0x03;
    OCR4C = 0xFF;
    TCCR4A = 0b10000010;
    TCCR4B = 0b00000001;
}