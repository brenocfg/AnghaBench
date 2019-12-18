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
 int PORTB ; 
 int PORTD ; 
 int PORTE ; 

__attribute__((used)) static void init_rows(void) {
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;

    DDRB  &= ~0b10000000;
    PORTB &= ~0b10000000;

    DDRE  &= ~0b00000100;
    PORTE |=  0b00000100;
}