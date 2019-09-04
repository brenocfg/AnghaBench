#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_3__ icount; scalar_t__ membase; int /*<<< orphan*/  dev; TYPE_2__* state; } ;
struct stm32_usart_offsets {scalar_t__ tdr; int /*<<< orphan*/  cr1; int /*<<< orphan*/  isr; int /*<<< orphan*/  cr3; } ;
struct stm32_port {int tx_dma_busy; TYPE_1__* info; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;
struct TYPE_4__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  USART_CR1_TXEIE ; 
 int /*<<< orphan*/  USART_CR3_DMAT ; 
 unsigned int USART_SR_TXE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed_poll_timeout_atomic (scalar_t__,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_set_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_transmit_chars_pio(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int isr;
	int ret;

	if (stm32_port->tx_dma_busy) {
		stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		stm32_port->tx_dma_busy = false;
	}

	ret = readl_relaxed_poll_timeout_atomic(port->membase + ofs->isr,
						isr,
						(isr & USART_SR_TXE),
						10, 100000);

	if (ret)
		dev_err(port->dev, "tx empty not set\n");

	stm32_set_bits(port, ofs->cr1, USART_CR1_TXEIE);

	writel_relaxed(xmit->buf[xmit->tail], port->membase + ofs->tdr);
	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	port->icount.tx++;
}