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
struct uart_port {TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct eg20t_port {int /*<<< orphan*/  desc_rx; int /*<<< orphan*/  trigger_level; int /*<<< orphan*/  sg_rx; struct uart_port port; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PCH_UART_HAL_RX_ERR_INT ; 
 int PCH_UART_HAL_RX_INT ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int dma_push_rx (struct eg20t_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_uart_hal_enable_interrupt (struct eg20t_port*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_dma_rx_complete(void *arg)
{
	struct eg20t_port *priv = arg;
	struct uart_port *port = &priv->port;
	int count;

	dma_sync_sg_for_cpu(port->dev, &priv->sg_rx, 1, DMA_FROM_DEVICE);
	count = dma_push_rx(priv, priv->trigger_level);
	if (count)
		tty_flip_buffer_push(&port->state->port);
	async_tx_ack(priv->desc_rx);
	pch_uart_hal_enable_interrupt(priv, PCH_UART_HAL_RX_INT |
					    PCH_UART_HAL_RX_ERR_INT);
}