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
 int /*<<< orphan*/  debounce_init (size_t) ; 
 int /*<<< orphan*/  i2c_init () ; 
 int /*<<< orphan*/  init_pins () ; 
 scalar_t__* matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 scalar_t__* raw_matrix ; 

void matrix_init(void) {

    // Initialize I2C
    i2c_init();

    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}