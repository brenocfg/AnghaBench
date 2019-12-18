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
typedef  int /*<<< orphan*/  mp_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/ * MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  board_stdio_uart ; 
 int /*<<< orphan*/  uart_tx_strn (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    if (MP_STATE_PORT(board_stdio_uart) != NULL) {
        uart_tx_strn(MP_STATE_PORT(board_stdio_uart), str, len);
    }
}