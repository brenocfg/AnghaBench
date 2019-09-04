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
struct uart_port {int dummy; } ;
struct sirfsoc_uart_port {TYPE_1__* uart_reg; int /*<<< orphan*/  is_atlas7; scalar_t__ rx_dma_chan; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_int_en_clr_reg; int /*<<< orphan*/  sirfsoc_int_en_reg; int /*<<< orphan*/  sirfsoc_rx_fifo_op; } ;
struct sirfsoc_int_en {int sirfsoc_rx_done_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  uart_type; struct sirfsoc_int_en uart_int_en; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 int SIRFUART_RX_DMA_INT_EN (struct sirfsoc_int_en*,int /*<<< orphan*/ ) ; 
 int SIRFUART_RX_IO_INT_EN (struct sirfsoc_int_en*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sirfsoc_uart_stop_rx(struct uart_port *port)
{
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_int_en *uint_en = &sirfport->uart_reg->uart_int_en;

	wr_regl(port, ureg->sirfsoc_rx_fifo_op, 0);
	if (sirfport->rx_dma_chan) {
		if (!sirfport->is_atlas7)
			wr_regl(port, ureg->sirfsoc_int_en_reg,
				rd_regl(port, ureg->sirfsoc_int_en_reg) &
				~(SIRFUART_RX_DMA_INT_EN(uint_en,
				sirfport->uart_reg->uart_type) |
				uint_en->sirfsoc_rx_done_en));
		else
			wr_regl(port, ureg->sirfsoc_int_en_clr_reg,
				SIRFUART_RX_DMA_INT_EN(uint_en,
				sirfport->uart_reg->uart_type)|
				uint_en->sirfsoc_rx_done_en);
		dmaengine_terminate_all(sirfport->rx_dma_chan);
	} else {
		if (!sirfport->is_atlas7)
			wr_regl(port, ureg->sirfsoc_int_en_reg,
				rd_regl(port, ureg->sirfsoc_int_en_reg)&
				~(SIRFUART_RX_IO_INT_EN(uint_en,
				sirfport->uart_reg->uart_type)));
		else
			wr_regl(port, ureg->sirfsoc_int_en_clr_reg,
				SIRFUART_RX_IO_INT_EN(uint_en,
				sirfport->uart_reg->uart_type));
	}
}