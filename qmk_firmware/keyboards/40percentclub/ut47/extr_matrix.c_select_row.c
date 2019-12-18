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
 int DDRC ; 
 int DDRD ; 
 int PORTC ; 
 int PORTD ; 

__attribute__((used)) static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRD  |= (1<<1);
            PORTD &= ~(1<<1);
            break;
        case 1:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 2:
            DDRD  |= (1<<4);
            PORTD &= ~(1<<4);
            break;
        case 3:
            DDRC  |= (1<<6);
            PORTC &= ~(1<<6);
            break;
    }
}