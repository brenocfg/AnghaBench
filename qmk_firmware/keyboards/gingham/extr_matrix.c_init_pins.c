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
 int PORT_EXPANDER_ADDRESS ; 
 int /*<<< orphan*/ * col_pins ; 
 int /*<<< orphan*/  i2c_writeReg (int,int,int*,int,int) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unselect_rows () ; 

__attribute__((used)) static void init_pins(void) {
    unselect_rows();
    // Set I/O
    uint8_t send_data = 0x07;
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x00, &send_data, 1, 20);
    // // Set Pull-up
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x06, &send_data, 1, 20);

    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if ( (x > 0) && (x < 12) ) {
        setPinInputHigh(col_pins[x]);
        }
    }
}