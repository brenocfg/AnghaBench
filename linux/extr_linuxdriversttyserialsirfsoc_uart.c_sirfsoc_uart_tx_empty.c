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
struct sirfsoc_uart_port {TYPE_1__* uart_reg; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_tx_fifo_status; } ;
struct sirfsoc_fifo_status {unsigned long (* ff_empty ) (struct uart_port*) ;} ;
struct TYPE_2__ {struct sirfsoc_fifo_status fifo_status; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct uart_port*) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 

__attribute__((used)) static inline unsigned int sirfsoc_uart_tx_empty(struct uart_port *port)
{
	unsigned long reg;
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_fifo_status *ufifo_st = &sirfport->uart_reg->fifo_status;
	reg = rd_regl(port, ureg->sirfsoc_tx_fifo_status);
	return (reg & ufifo_st->ff_empty(port)) ? TIOCSER_TEMT : 0;
}