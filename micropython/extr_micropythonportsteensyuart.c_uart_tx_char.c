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
typedef  int /*<<< orphan*/  pyb_uart_obj_t ;

/* Variables and functions */

void uart_tx_char(pyb_uart_obj_t *uart_obj, int c) {
#if 0
    uint8_t ch = c;
    HAL_UART_Transmit(&uart_obj->uart, &ch, 1, 100000);
#endif
}