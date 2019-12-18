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
 int /*<<< orphan*/ * col_pins ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unselect_cols(void) {
    for (uint8_t x = 0; x < 6; x++) {
        setPinOutput(col_pins[x]);
        writePinLow(col_pins[x]);
    }
}