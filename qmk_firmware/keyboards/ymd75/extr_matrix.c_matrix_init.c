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
 int DDRA ; 
 int DDRB ; 
 int DDRC ; 
 int DDRD ; 
 size_t MATRIX_ROWS ; 
 int PIND7 ; 
 int PORTA ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int* matrix ; 
 int* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 

void matrix_init(void) {
    // all outputs for rows high
    DDRB = 0xFF;
    PORTB = 0xFF;
    // all inputs for columns
    DDRA = 0x00;
    DDRC &= ~(0x111111<<2);
    DDRD &= ~(1<<PIND7);
    // all columns are pulled-up
    PORTA = 0xFF;
    PORTC |= (0b111111<<2);
    PORTD |= (1<<PIND7);

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0x00;
        matrix_debouncing[row] = 0x00;
    }
    matrix_init_quantum();  // missing from original port by Luiz
}