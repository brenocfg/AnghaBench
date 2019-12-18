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
 size_t MATRIX_ROWS ; 
 int /*<<< orphan*/  init_cols () ; 
 int /*<<< orphan*/  init_data () ; 
 int /*<<< orphan*/  init_led () ; 
 int /*<<< orphan*/  init_rows () ; 
 int /*<<< orphan*/  init_strobe () ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debounce ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 

void matrix_init(void) {
    init_led()    ;   
    init_rows()   ;
    init_cols()   ;
    init_data()   ;
    init_strobe() ;
    
    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i]            = 0;
#       if (DEBOUNCE > 0)
        matrix_debounce  [i] = 0;
#       endif
    }

    matrix_init_quantum() ;
}