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
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTF ; 

void set_led_state(int ledId, bool state)
{
    if (state)
    {
        switch (ledId)
        {
        case 0:
            PORTD |= (1 << 6);
            break;
        case 1:
            PORTB |= (1 << 6);
            break;
        case 2:
            PORTF |= (1 << 5);
            break;
        case 3:
            PORTB |= (1 << 4);
            break;
        case 4:
            PORTC |= (1 << 7);
            break;
        case 5:
            PORTF |= (1 << 7);
            break;
        }
    }
    else
    {
        switch (ledId)
        {
        case 0:
            PORTD &= ~(1 << 6);
            break;
        case 1:
            PORTB &= ~(1 << 6);
            break;
        case 2:
            PORTF &= ~(1 << 5);
            break;
        case 3:
            PORTB &= ~(1 << 4);
            break;
        case 4:
            PORTC &= ~(1 << 7);
            break;
        case 5:
            PORTF &= ~(1 << 7);
            break;
        }
    }
}