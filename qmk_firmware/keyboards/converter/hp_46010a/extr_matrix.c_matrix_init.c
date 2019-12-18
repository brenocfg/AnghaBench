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
 int /*<<< orphan*/  DDRD ; 
 int /*<<< orphan*/  LED ; 
 int /*<<< orphan*/  Matrix_Reset () ; 
 int PORTB ; 
 int /*<<< orphan*/  PORTD ; 
 int RESET ; 
 int SCLK ; 
 int SDATA ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 

void matrix_init () {
    // debug_matrix = 1;
    // PB0 (SS) and PB1 (SCLK) set to outputs
    DDRB |= RESET | SCLK ;
    // PB2, is unused, and PB3 is our serial input
    DDRB &= ~SDATA ;
    
    // SS is reset for this board, and is active High
    // SCLK is the serial clock and is active High
    PORTB &= ~RESET ;
    PORTB |= SCLK   ;

    // led pin
    DDRD  |= LED ;
    PORTD &= ~LED ;

    matrix_init_quantum();

    //toggle reset, to put the keyboard logic into a known state
    Matrix_Reset() ;
}