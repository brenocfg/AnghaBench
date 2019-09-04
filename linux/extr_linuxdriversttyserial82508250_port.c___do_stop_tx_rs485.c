#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ rs485; } ;
struct uart_8250_port {int ier; TYPE_2__ port; } ;

/* Variables and functions */
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  serial8250_clear_and_reinit_fifos (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_em485_rts_after_send (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_port_out (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __do_stop_tx_rs485(struct uart_8250_port *p)
{
	serial8250_em485_rts_after_send(p);

	/*
	 * Empty the RX FIFO, we are not interested in anything
	 * received during the half-duplex transmission.
	 * Enable previously disabled RX interrupts.
	 */
	if (!(p->port.rs485.flags & SER_RS485_RX_DURING_TX)) {
		serial8250_clear_and_reinit_fifos(p);

		p->ier |= UART_IER_RLSI | UART_IER_RDI;
		serial_port_out(&p->port, UART_IER, p->ier);
	}
}