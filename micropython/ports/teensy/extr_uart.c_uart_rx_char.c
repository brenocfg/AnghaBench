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
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  uart; } ;
typedef  TYPE_1__ pyb_uart_obj_t ;

/* Variables and functions */
 scalar_t__ HAL_OK ; 
 scalar_t__ HAL_UART_Receive (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 

int uart_rx_char(pyb_uart_obj_t *uart_obj) {
    uint8_t ch;
#if 0
    if (HAL_UART_Receive(&uart_obj->uart, &ch, 1, 0) != HAL_OK) {
        ch = 0;
    }
#else
    ch = 'A';
#endif
    return ch;
}