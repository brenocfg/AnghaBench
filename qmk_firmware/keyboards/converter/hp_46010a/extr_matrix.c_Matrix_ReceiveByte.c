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
 int MATRIX_COLS ; 
 int PINB ; 
 int /*<<< orphan*/  SCLK_increment () ; 
 int SDATA ; 

__attribute__((used)) inline
static
uint8_t Matrix_ReceiveByte (void) {
    uint8_t received = 0 ;
    uint8_t temp     = 0 ;
    for ( uint8_t bit = 0; bit < MATRIX_COLS; ++bit ) {
        // toggle the clock
        SCLK_increment();
        temp      = (PINB & SDATA) << 4 ;
        received |= temp >> bit ;
    }

    return received ;
}