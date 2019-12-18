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
 int /*<<< orphan*/  SCLK_increment () ; 

__attribute__((used)) inline
static
void Matrix_ThrowByte(void) {
    // we use MATRIX_COLS - 1 here because that would put us at 7 clocks
    for ( uint8_t bit = 0; bit < MATRIX_COLS - 1; ++bit ) {
        // toggle the clock
        SCLK_increment();
    }
    
    return ;
}