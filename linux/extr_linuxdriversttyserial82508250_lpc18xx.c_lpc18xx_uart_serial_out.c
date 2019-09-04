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
struct uart_port {int regshift; scalar_t__ membase; } ;

/* Variables and functions */
 int UART_FCR ; 
 int UART_FCR_DMA_SELECT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void lpc18xx_uart_serial_out(struct uart_port *p, int offset, int value)
{
	/*
	 * For DMA mode one must ensure that the UART_FCR_DMA_SELECT
	 * bit is set when FIFO is enabled. Even if DMA is not used
	 * setting this bit doesn't seem to affect anything.
	 */
	if (offset == UART_FCR && (value & UART_FCR_ENABLE_FIFO))
		value |= UART_FCR_DMA_SELECT;

	offset = offset << p->regshift;
	writel(value, p->membase + offset);
}