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
 int /*<<< orphan*/  uart_interrupt_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_ring_esp_gps ; 

void USART1_IRQHandler(void) { uart_interrupt_handler(&uart_ring_esp_gps); }