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
struct uart_port {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCSCR ; 
 unsigned short SCSCR_TDRQE ; 
 unsigned short SCSCR_TIE ; 
 unsigned short serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void sci_stop_tx(struct uart_port *port)
{
	unsigned short ctrl;

	/* Clear TIE (Transmit Interrupt Enable) bit in SCSCR */
	ctrl = serial_port_in(port, SCSCR);

	if (port->type == PORT_SCIFA || port->type == PORT_SCIFB)
		ctrl &= ~SCSCR_TDRQE;

	ctrl &= ~SCSCR_TIE;

	serial_port_out(port, SCSCR, ctrl);
}