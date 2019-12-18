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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * col_select_pins ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mux_pin_control(const uint8_t binary[]) {
    // set pin0
    setPinOutput(col_select_pins[0]);
    if(binary[2] == 0) {
        writePinLow(col_select_pins[0]);
    }
    else {
        writePinHigh(col_select_pins[0]);
    }
    // set pin1
    setPinOutput(col_select_pins[1]);
    if(binary[1] == 0) {
        writePinLow(col_select_pins[1]);
    }
    else {
        writePinHigh(col_select_pins[1]);
    }
    // set pin2
    setPinOutput(col_select_pins[2]);
    if(binary[0] == 0) {
        writePinLow(col_select_pins[2]);
    }
    else {
        writePinHigh(col_select_pins[2]);
    }
}