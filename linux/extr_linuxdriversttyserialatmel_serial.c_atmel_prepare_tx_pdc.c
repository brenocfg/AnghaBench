#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct circ_buf {int /*<<< orphan*/  buf; } ;
struct atmel_dma_buffer {scalar_t__ ofs; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  dma_addr; } ;
struct atmel_uart_port {struct atmel_dma_buffer pdc_tx; } ;
struct TYPE_2__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static int atmel_prepare_tx_pdc(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct atmel_dma_buffer *pdc = &atmel_port->pdc_tx;
	struct circ_buf *xmit = &port->state->xmit;

	pdc->buf = xmit->buf;
	pdc->dma_addr = dma_map_single(port->dev,
					pdc->buf,
					UART_XMIT_SIZE,
					DMA_TO_DEVICE);
	pdc->dma_size = UART_XMIT_SIZE;
	pdc->ofs = 0;

	return 0;
}