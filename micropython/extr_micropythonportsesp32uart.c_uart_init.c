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
typedef  int /*<<< orphan*/  uart_isr_handle_t ;

/* Variables and functions */
 int ESP_INTR_FLAG_IRAM ; 
 int ESP_INTR_FLAG_LOWMED ; 
 int /*<<< orphan*/  UART_NUM_0 ; 
 int /*<<< orphan*/  uart_enable_rx_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_irq_handler ; 
 int /*<<< orphan*/  uart_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void uart_init(void) {
    uart_isr_handle_t handle;
    uart_isr_register(UART_NUM_0, uart_irq_handler, NULL, ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_IRAM, &handle);
    uart_enable_rx_intr(UART_NUM_0);
}