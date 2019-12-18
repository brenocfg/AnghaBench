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
typedef  size_t uint8_t ;

/* Variables and functions */
 int DDRB ; 
 int DDRC ; 
 int DDRD ; 
 int DDRF ; 
 size_t MATRIX_ROWS ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTF ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  unselect_rows () ; 

void matrix_init(void)
{
    //debug_enable = true;
    
    //dprint("matrix_init"); dprintln();
    // output high (leds)
    DDRD    = 0xFF;
    PORTD   = 0xFF;
    
    // output low (multiplexers)
    DDRF    = 0xFF;
    PORTF   = 0x00;
    
    // input with pullup (matrix)
    DDRB    = 0x00;
    PORTB   = 0xFF;
    
    // input with pullup (program and keypad buttons)
    DDRC    = 0x00;
    PORTC   = 0xFF;
    
    // initialize row and col
    unselect_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
	
}