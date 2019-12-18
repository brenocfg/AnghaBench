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
 int /*<<< orphan*/ * MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __WFI () ; 
 int /*<<< orphan*/  board_stdio_uart ; 
 scalar_t__ uart_rx_any (int /*<<< orphan*/ *) ; 
 int uart_rx_char (int /*<<< orphan*/ *) ; 

int mp_hal_stdin_rx_chr(void) {
    for (;;) {
        if (MP_STATE_PORT(board_stdio_uart) != NULL && uart_rx_any(MP_STATE_PORT(board_stdio_uart))) {
            return uart_rx_char(MP_STATE_PORT(board_stdio_uart));
        }
        __WFI();
    }

    return 0;
}