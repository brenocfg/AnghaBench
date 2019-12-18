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
 int GPPUA ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 int IODIRA ; 
 int MATRIX_COLS ; 
 int MATRIX_ROWS ; 
 scalar_t__* col_expanded ; 
 int* expander_col_pins ; 
 int expander_input_pin_mask ; 
 int* expander_row_pins ; 
 scalar_t__ expander_status ; 
 int /*<<< orphan*/  i2c_init () ; 
 int /*<<< orphan*/  i2c_initialized ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int) ; 
 int /*<<< orphan*/  wait_us (int) ; 

void init_expander(void) {
    if (! i2c_initialized) {
        i2c_init();
        wait_us(1000000);
    }

    if (! expander_input_pin_mask) {
#if (DIODE_DIRECTION == COL2ROW)
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (col_expanded[col]) {
                expander_input_pin_mask |= (1 << expander_col_pins[col]);
            }
        }
#elif (DIODE_DIRECTION == ROW2COL)
        for (int row = 0; row < MATRIX_ROWS; row++) {
            expander_input_pin_mask |= (1 << expander_row_pins[row]);
        }
#endif
    }

    expander_status = i2c_start(I2C_ADDR_WRITE); if (expander_status) goto out;
    expander_status = i2c_write(IODIRA);         if (expander_status) goto out;

    /*
    Pin direction and pull-up depends on both the diode direction
    and on whether the column register is GPIOA or GPIOB
    +-------+---------------+---------------+
    |       | ROW2COL       | COL2ROW       |
    +-------+---------------+---------------+
    | GPIOA | input, output | output, input |
    +-------+---------------+---------------+
    | GPIOB | output, input | input, output |
    +-------+---------------+---------------+
    */

#if (EXPANDER_COL_REGISTER == GPIOA)
#   if (DIODE_DIRECTION == COL2ROW)
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
        expander_status = i2c_write(0);                       if (expander_status) goto out;
#   elif (DIODE_DIRECTION == ROW2COL)
        expander_status = i2c_write(0);                       if (expander_status) goto out;
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
#   endif
#elif (EXPANDER_COL_REGISTER == GPIOB)
#   if (DIODE_DIRECTION == COL2ROW)
        expander_status = i2c_write(0);                       if (expander_status) goto out;
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
#   elif (DIODE_DIRECTION == ROW2COL)
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
        expander_status = i2c_write(0);                       if (expander_status) goto out;
#   endif
#endif

    i2c_stop();

    // set pull-up
    // - unused  : off : 0
    // - input   : on  : 1
    // - driving : off : 0
    expander_status = i2c_start(I2C_ADDR_WRITE);              if (expander_status) goto out;
    expander_status = i2c_write(GPPUA);                       if (expander_status) goto out;
#if (EXPANDER_COL_REGISTER == GPIOA)
#   if (DIODE_DIRECTION == COL2ROW)
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
        expander_status = i2c_write(0);                       if (expander_status) goto out;
#   elif (DIODE_DIRECTION == ROW2COL)
        expander_status = i2c_write(0);                       if (expander_status) goto out;
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
#   endif
#elif (EXPANDER_COL_REGISTER == GPIOB)
#   if (DIODE_DIRECTION == COL2ROW)
        expander_status = i2c_write(0);                       if (expander_status) goto out;
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
#   elif (DIODE_DIRECTION == ROW2COL)
        expander_status = i2c_write(expander_input_pin_mask); if (expander_status) goto out;
        expander_status = i2c_write(0);                       if (expander_status) goto out;
#   endif
#endif

out:
    i2c_stop();
}