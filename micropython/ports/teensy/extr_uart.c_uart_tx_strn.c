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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint ;
struct TYPE_3__ {int /*<<< orphan*/  uart; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_UART_Transmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void uart_tx_strn(pyb_uart_obj_t *uart_obj, const char *str, uint len) {
#if 0
    HAL_UART_Transmit(&uart_obj->uart, (uint8_t*)str, len, 100000);
#endif
}