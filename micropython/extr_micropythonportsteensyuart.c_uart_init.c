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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pyb_uart_obj_t ;

/* Variables and functions */
 int uart_init2 (int /*<<< orphan*/ *) ; 

bool uart_init(pyb_uart_obj_t *uart_obj, uint32_t baudrate) {
#if 0
    UART_HandleTypeDef *uh = &uart_obj->uart;
    memset(uh, 0, sizeof(*uh));
    uh->Init.BaudRate = baudrate;
    uh->Init.WordLength = UART_WORDLENGTH_8B;
    uh->Init.StopBits = UART_STOPBITS_1;
    uh->Init.Parity = UART_PARITY_NONE;
    uh->Init.Mode = UART_MODE_TX_RX;
    uh->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uh->Init.OverSampling = UART_OVERSAMPLING_16;
#endif
    return uart_init2(uart_obj);
}