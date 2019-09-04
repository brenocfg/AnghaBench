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
typedef  int /*<<< orphan*/  mp_uint_t ;

/* Variables and functions */

mp_uint_t uart_rx_any(pyb_uart_obj_t *uart_obj) {
#if 0
    return __HAL_UART_GET_FLAG(&uart_obj->uart, UART_FLAG_RXNE);
#else
    return 0;
#endif
}