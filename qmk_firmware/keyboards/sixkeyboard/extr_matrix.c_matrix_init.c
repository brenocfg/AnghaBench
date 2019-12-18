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
 size_t MATRIX_ROWS ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 scalar_t__* matrix_stage ; 

void matrix_init(void)
{

    DDRC  &= ~(1<<7);
    PORTC |=  (1<<7);
    DDRB  &= ~(1<<7 | 1<<5);
    PORTB |=  (1<<7 | 1<<5);
    DDRD  &= ~(1<<6 | 1<<4 | 1<<1);
    PORTD |=  (1<<6 | 1<<4 | 1<<1);

    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
        matrix_stage[i] = 0;
    }

    matrix_init_quantum();

}