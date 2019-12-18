#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  OverSampling; int /*<<< orphan*/  HwFlowCtl; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Parity; int /*<<< orphan*/  StopBits; int /*<<< orphan*/  WordLength; int /*<<< orphan*/  BaudRate; } ;
struct TYPE_9__ {TYPE_1__ Init; } ;
struct TYPE_8__ {TYPE_3__ uart; } ;
typedef  TYPE_2__ pyb_uart_obj_t ;
typedef  TYPE_3__ UART_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  UART_HWCONTROL_NONE ; 
 int /*<<< orphan*/  UART_MODE_TX_RX ; 
 int /*<<< orphan*/  UART_OVERSAMPLING_16 ; 
 int /*<<< orphan*/  UART_PARITY_NONE ; 
 int /*<<< orphan*/  UART_STOPBITS_1 ; 
 int /*<<< orphan*/  UART_WORDLENGTH_8B ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int uart_init2 (TYPE_2__*) ; 

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