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
typedef  int matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ENABLE () ; 
 int /*<<< orphan*/  KEY_HYS_OFF () ; 
 int /*<<< orphan*/  KEY_HYS_ON () ; 
 scalar_t__ KEY_STATE () ; 
 int /*<<< orphan*/  KEY_UNABLE () ; 
 scalar_t__ MATRIX_COLS ; 
 scalar_t__ MATRIX_ROWS ; 
 int /*<<< orphan*/  SET_COL (scalar_t__) ; 
 int /*<<< orphan*/  SET_ROW (scalar_t__) ; 
 int TIMER_DIFF_RAW (scalar_t__,scalar_t__) ; 
 scalar_t__ TIMER_RAW ; 
 int TIMER_RAW_FREQ ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_last_modified ; 
 int* matrix_prev ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  timer_read32 () ; 

uint8_t matrix_scan(void)
{
    matrix_row_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    uint8_t row, col;
    for (col = 0; col < MATRIX_COLS; col++) {
        SET_COL(col);
        for (row = 0; row < MATRIX_ROWS; row++) {
            //KEY_SELECT(row, col);
            SET_ROW(row);
            _delay_us(2);

            // Not sure this is needed. This just emulates HHKB controller's behaviour.
            if (matrix_prev[row] & (1<<col)) {
                KEY_HYS_ON();
            }
            _delay_us(10);

            // NOTE: KEY_STATE is valid only in 20us after KEY_ENABLE.
            // If V-USB interrupts in this section we could lose 40us or so
            // and would read invalid value from KEY_STATE.
            uint8_t last = TIMER_RAW;

            KEY_ENABLE();

            // Wait for KEY_STATE outputs its value.
            _delay_us(2);

            if (KEY_STATE()) {
                matrix[row] &= ~(1<<col);
            } else {
                matrix[row] |= (1<<col);
            }

            // Ignore if this code region execution time elapses more than 20us.
            // MEMO: 20[us] * (TIMER_RAW_FREQ / 1000000)[count per us]
            // MEMO: then change above using this rule: a/(b/c) = a*1/(b/c) = a*(c/b)
            if (TIMER_DIFF_RAW(TIMER_RAW, last) > 20/(1000000/TIMER_RAW_FREQ)) {
                matrix[row] = matrix_prev[row];
            }

            _delay_us(5);
            KEY_HYS_OFF();
            KEY_UNABLE();

            // NOTE: KEY_STATE keep its state in 20us after KEY_ENABLE.
            // This takes 25us or more to make sure KEY_STATE returns to idle state.
            _delay_us(75);
        }
        if (matrix[row] ^ matrix_prev[row]) {
            matrix_last_modified = timer_read32();
        }
    }
    matrix_scan_quantum();
    return 1;
}