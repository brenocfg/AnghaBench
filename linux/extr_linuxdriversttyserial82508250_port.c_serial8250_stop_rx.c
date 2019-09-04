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
struct TYPE_2__ {int /*<<< orphan*/  read_status_mask; } ;
struct uart_8250_port {int ier; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_LSR_DR ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void serial8250_stop_rx(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);

	serial8250_rpm_get(up);

	up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
	up->port.read_status_mask &= ~UART_LSR_DR;
	serial_port_out(port, UART_IER, up->ier);

	serial8250_rpm_put(up);
}