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
 int PORTD ; 

__attribute__((used)) static void select_col(uint8_t col) {
    switch (col) {
        case  0: PORTD = (PORTD & ~0b01111011) | 0b00011011; break;
        case  1: PORTD = (PORTD & ~0b01111011) | 0b01000011; break;
        case  2: PORTD = (PORTD & ~0b01111011) | 0b01101010; break;
        case  3: PORTD = (PORTD & ~0b01111011) | 0b01111001; break;
        case  4: PORTD = (PORTD & ~0b01111011) | 0b01100010; break;
        case  5: PORTD = (PORTD & ~0b01111011) | 0b01110001; break;
        case  6: PORTD = (PORTD & ~0b01111011) | 0b01100001; break;
        case  7: PORTD = (PORTD & ~0b01111011) | 0b01110000; break;
        case  8: PORTD = (PORTD & ~0b01111011) | 0b01100000; break;
        case  9: PORTD = (PORTD & ~0b01111011) | 0b01101000; break;
        case 10: PORTD = (PORTD & ~0b01111011) | 0b00101011; break;
        case 11: PORTD = (PORTD & ~0b01111011) | 0b00110011; break;
        case 12: PORTD = (PORTD & ~0b01111011) | 0b00100011; break;
        case 13: PORTD = (PORTD & ~0b01111011) | 0b01111000; break;
        case 14: PORTD = (PORTD & ~0b01111011) | 0b00010011; break;
        case 15: PORTD = (PORTD & ~0b01111011) | 0b01101001; break;
        case 16: PORTD = (PORTD & ~0b01111011) | 0b00001011; break;
        case 17: PORTD = (PORTD & ~0b01111011) | 0b00111011; break;
    }
}