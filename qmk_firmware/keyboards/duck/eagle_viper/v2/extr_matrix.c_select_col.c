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
 int PORTF ; 

__attribute__((used)) static void select_col(uint8_t col) {
 
   switch (col) {
        case 0:
            PORTC |= 0b01000000;
            break;
        case 1:
            PORTC |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 2:
            PORTC |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 3:
            PORTC |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 4:
            PORTC |= 0b11000000;
            break;
        case 5:
            PORTC |= 0b11000000;
            PORTF |= 0b00000001;
            break;
        case 6:
            PORTC |= 0b11000000;
            PORTF |= 0b00000010;
            break;
        case 7:
            PORTC |= 0b11000000;
            PORTF |= 0b00000011;
            break;
        case 8:
            PORTB |= 0b01000000;
            break;
        case 9:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 10:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 11:
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 12:
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            break;
        case 13:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            PORTC |= 0b10000000;
            break;
        case 14:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            PORTC |= 0b10000000;
            break;
    }
}