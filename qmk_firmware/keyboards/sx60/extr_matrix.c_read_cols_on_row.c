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
typedef  int uint16_t ;
typedef  int matrix_row_t ;

/* Variables and functions */
 size_t ATMEGA_COLS ; 
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  I2C_ADDR_READ ; 
 int /*<<< orphan*/  I2C_ADDR_WRITE ; 
 size_t ROW_SHIFTER ; 
 size_t _BV (size_t) ; 
 size_t _SFR_IO8 (size_t) ; 
 size_t* col_pins ; 
 int i2c_readNak () ; 
 scalar_t__ i2c_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_stop () ; 
 scalar_t__ i2c_write (int /*<<< orphan*/ ) ; 
 scalar_t__ mcp23018_status ; 
 int /*<<< orphan*/  select_row (size_t) ; 
 int /*<<< orphan*/  unselect_rows () ; 
 int /*<<< orphan*/  wait_us (int) ; 

__attribute__((used)) static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    /* Store last value of row prior to reading */
    matrix_row_t last_row_value = current_matrix[current_row];

    /* Clear data in matrix row */
    current_matrix[current_row] = 0;

    /* Select row and wait for row selecton to stabilize */
    select_row(current_row);
    wait_us(30);

    if (mcp23018_status) {
        /* if there was an error */
        return 0;
    } else {
        uint16_t data = 0;
        mcp23018_status = i2c_start(I2C_ADDR_WRITE);    if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOA);             if (mcp23018_status) goto out;
        mcp23018_status = i2c_start(I2C_ADDR_READ);     if (mcp23018_status) goto out;
        data = i2c_readNak();
        data = ~data;
    out:
        i2c_stop();
        current_matrix[current_row] |= (data << 8);
    }

    /* For each col... */
    for(uint8_t col_index = 0; col_index < ATMEGA_COLS; col_index++) {
        /* Select the col pin to read (active low) */
        uint8_t pin = col_pins[col_index];
        uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

        /* Populate the matrix row with the state of the col pin */
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
    }

    /* Unselect row */
    unselect_rows();

    return (last_row_value != current_matrix[current_row]);
}