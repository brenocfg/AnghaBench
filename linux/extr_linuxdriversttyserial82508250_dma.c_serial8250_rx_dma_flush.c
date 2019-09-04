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
struct uart_8250_port {struct uart_8250_dma* dma; } ;
struct uart_8250_dma {int /*<<< orphan*/  rxchan; scalar_t__ rx_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_rx_complete (struct uart_8250_port*) ; 
 int /*<<< orphan*/  dmaengine_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 

void serial8250_rx_dma_flush(struct uart_8250_port *p)
{
	struct uart_8250_dma *dma = p->dma;

	if (dma->rx_running) {
		dmaengine_pause(dma->rxchan);
		__dma_rx_complete(p);
		dmaengine_terminate_async(dma->rxchan);
	}
}