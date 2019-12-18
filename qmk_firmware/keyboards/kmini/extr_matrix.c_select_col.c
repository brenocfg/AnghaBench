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
typedef  int uint8_t ;

/* Variables and functions */
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 
 int PORTF ; 

__attribute__((used)) static void select_col(uint8_t col)
{
    switch (col) {
        case 0:
            PORTB |= (1<<5); // HI
            break;
        case 1:
            PORTB |= (1<<6); // HI
            break;
        case 2:
            PORTC |= (1<<6); // HI
            break;
        case 3:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<0); // HI
            break;
        case 4:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<1); // HI
            break;
        case 5:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<0); // HI
            PORTF |= (1<<1); // HI
            break;
        case 6:
            PORTC |= (1<<6); // HI
            PORTC |= (1<<7); // HI
            break;
        case 7:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<0); // HI
            PORTC |= (1<<7); // HI
            break;
        case 8:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<1); // HI
            PORTC |= (1<<7); // HI
            break;
        case 9:
            PORTC |= (1<<6); // HI
            PORTF |= (1<<0); // HI
            PORTF |= (1<<1); // HI
            PORTC |= (1<<7); // HI
            break;
        case 10:
            PORTE |= (1<<6); // HI
            break;
        case 11:
            PORTB |= (1<<0); // HI
            break;
        case 12:
            PORTB |= (1<<7); // HI
            break;
        case 13:
            PORTD |= (1<<4); // HI
            break;
        case 14:
            PORTD |= (1<<6); // HI
            break;
        case 15:
            PORTD |= (1<<7); // HI
            break;
        case 16:
            PORTB |= (1<<4); // HI
            break;
    }
}