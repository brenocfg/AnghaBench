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
 scalar_t__ DEVICE_STATE_Suspended ; 
 scalar_t__ DEVICE_STATE_Unattached ; 
 int /*<<< orphan*/  KEY_ENABLE () ; 
 int /*<<< orphan*/  KEY_POWER_OFF () ; 
 int /*<<< orphan*/  KEY_POWER_ON () ; 
 scalar_t__ KEY_POWER_STATE () ; 
 int /*<<< orphan*/  KEY_PREV_OFF () ; 
 int /*<<< orphan*/  KEY_PREV_ON () ; 
 int /*<<< orphan*/  KEY_SELECT (size_t,size_t) ; 
 scalar_t__ KEY_STATE () ; 
 int /*<<< orphan*/  KEY_UNABLE () ; 
 size_t MATRIX_COLS ; 
 scalar_t__ MATRIX_POWER_SAVE ; 
 size_t MATRIX_ROWS ; 
 int TIMER_DIFF_RAW (size_t,size_t) ; 
 size_t TIMER_RAW ; 
 int TIMER_RAW_FREQ ; 
 scalar_t__ USB_DeviceState ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_last_modified ; 
 int* matrix_prev ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  suspend_power_down () ; 
 scalar_t__ timer_elapsed32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 

uint8_t matrix_scan(void)
{
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    // power on
    if (!KEY_POWER_STATE()) KEY_POWER_ON();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            KEY_SELECT(row, col);
            _delay_us(5);

            // Not sure this is needed. This just emulates HHKB controller's behaviour.
            if (matrix_prev[row] & (1<<col)) {
                KEY_PREV_ON();
            }
            _delay_us(10);

            // NOTE: KEY_STATE is valid only in 20us after KEY_ENABLE.
            // If V-USB interrupts in this section we could lose 40us or so
            // and would read invalid value from KEY_STATE.
            uint8_t last = TIMER_RAW;

            KEY_ENABLE();

            // Wait for KEY_STATE outputs its value.
            // 1us was ok on one HHKB, but not worked on another.
            // no   wait doesn't work on Teensy++ with pro(1us works)
            // no   wait does    work on tmk PCB(8MHz) with pro2
            // 1us  wait does    work on both of above
            // 1us  wait doesn't work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz/2)
            // 5us  wait does    work on tmk(8MHz)
            // 10us wait does    work on Teensy++ with pro
            // 10us wait does    work on 328p+iwrap with pro
            // 10us wait doesn't work on tmk PCB(8MHz) with pro2(very lagged scan)
            _delay_us(5);

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
            KEY_PREV_OFF();
            KEY_UNABLE();

            // NOTE: KEY_STATE keep its state in 20us after KEY_ENABLE.
            // This takes 25us or more to make sure KEY_STATE returns to idle state.
#ifdef HHKB_JP
            // Looks like JP needs faster scan due to its twice larger matrix
            // or it can drop keys in fast key typing
            _delay_us(30);
#else
            _delay_us(75);
#endif
        }
        if (matrix[row] ^ matrix_prev[row]) matrix_last_modified = timer_read32();
    }
    // power off
    if (KEY_POWER_STATE() &&
            (USB_DeviceState == DEVICE_STATE_Suspended ||
             USB_DeviceState == DEVICE_STATE_Unattached ) &&
            timer_elapsed32(matrix_last_modified) > MATRIX_POWER_SAVE) {
        KEY_POWER_OFF();
        suspend_power_down();
    }

    matrix_scan_quantum();

    return 1;
}