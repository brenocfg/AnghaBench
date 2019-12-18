#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uart; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;
typedef  int /*<<< orphan*/  mp_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FLAG_RXNE ; 
 int /*<<< orphan*/  __HAL_UART_GET_FLAG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_uint_t uart_rx_any(pyb_uart_obj_t *uart_obj) {
#if 0
    return __HAL_UART_GET_FLAG(&uart_obj->uart, UART_FLAG_RXNE);
#else
    return 0;
#endif
}