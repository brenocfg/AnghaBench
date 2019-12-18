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
 int /*<<< orphan*/  E2 ; 
 size_t MATRIX_ROWS ; 
 int /*<<< orphan*/ * row_pins ; 
 int /*<<< orphan*/  setPinInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unselect_cols () ; 

__attribute__((used)) static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInput(row_pins[x]);
    }

    setPinInputHigh(E2);
}