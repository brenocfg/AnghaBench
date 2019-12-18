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
 int /*<<< orphan*/  A10 ; 
 int /*<<< orphan*/  A8 ; 
 int /*<<< orphan*/  A9 ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    setPinOutput(A8);
    setPinOutput(A9);
    setPinOutput(A10);
    writePinLow(A8);
    writePinLow(A9);
    writePinLow(A10);

    matrix_init_user();
}