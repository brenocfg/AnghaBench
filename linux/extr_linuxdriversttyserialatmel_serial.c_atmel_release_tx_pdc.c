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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct atmel_dma_buffer {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  dma_addr; } ;
struct atmel_uart_port {struct atmel_dma_buffer pdc_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_release_tx_pdc(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct atmel_dma_buffer *pdc = &atmel_port->pdc_tx;

	dma_unmap_single(port->dev,
			 pdc->dma_addr,
			 pdc->dma_size,
			 DMA_TO_DEVICE);
}