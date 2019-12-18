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
 int DDRF ; 
 int PORTB ; 
 int PORTC ; 
 int PORTF ; 

__attribute__((used)) static void unselect_cols(void) {
    DDRB  |=  0b01000000; // PB6 (U2) output
    PORTB &= ~0b01000000; // PB6 (U2) low

    DDRC  |=  0b11000000; // PC6 (U1), PC7 (A2) output
    PORTC &= ~0b11000000; // PC6 (U1), PC7 (A2) low

    DDRF  |=  0b00000011; // PF0 (A0), PF1 (A1) output
    PORTF &= ~0b00000011; // PF0 (A0), PF1 (A1) low
}