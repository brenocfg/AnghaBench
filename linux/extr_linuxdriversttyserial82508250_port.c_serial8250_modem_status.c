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
struct TYPE_4__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct uart_port {TYPE_3__* state; TYPE_1__ icount; } ;
struct uart_8250_port {unsigned int msr_saved_flags; int ier; struct uart_port port; } ;
struct TYPE_5__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {TYPE_2__ port; } ;

/* Variables and functions */
 int UART_IER_MSI ; 
 int /*<<< orphan*/  UART_MSR ; 
 unsigned int UART_MSR_ANY_DELTA ; 
 unsigned int UART_MSR_CTS ; 
 unsigned int UART_MSR_DCD ; 
 unsigned int UART_MSR_DCTS ; 
 unsigned int UART_MSR_DDCD ; 
 unsigned int UART_MSR_DDSR ; 
 unsigned int UART_MSR_TERI ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

unsigned int serial8250_modem_status(struct uart_8250_port *up)
{
	struct uart_port *port = &up->port;
	unsigned int status = serial_in(up, UART_MSR);

	status |= up->msr_saved_flags;
	up->msr_saved_flags = 0;
	if (status & UART_MSR_ANY_DELTA && up->ier & UART_IER_MSI &&
	    port->state != NULL) {
		if (status & UART_MSR_TERI)
			port->icount.rng++;
		if (status & UART_MSR_DDSR)
			port->icount.dsr++;
		if (status & UART_MSR_DDCD)
			uart_handle_dcd_change(port, status & UART_MSR_DCD);
		if (status & UART_MSR_DCTS)
			uart_handle_cts_change(port, status & UART_MSR_CTS);

		wake_up_interruptible(&port->state->port.delta_msr_wait);
	}

	return status;
}