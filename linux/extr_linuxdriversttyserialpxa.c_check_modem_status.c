#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct TYPE_9__ {TYPE_2__* state; TYPE_3__ icount; } ;
struct uart_pxa_port {TYPE_4__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_MSR ; 
 int UART_MSR_ANY_DELTA ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_TERI ; 
 int serial_in (struct uart_pxa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_4__*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void check_modem_status(struct uart_pxa_port *up)
{
	int status;

	status = serial_in(up, UART_MSR);

	if ((status & UART_MSR_ANY_DELTA) == 0)
		return;

	if (status & UART_MSR_TERI)
		up->port.icount.rng++;
	if (status & UART_MSR_DDSR)
		up->port.icount.dsr++;
	if (status & UART_MSR_DDCD)
		uart_handle_dcd_change(&up->port, status & UART_MSR_DCD);
	if (status & UART_MSR_DCTS)
		uart_handle_cts_change(&up->port, status & UART_MSR_CTS);

	wake_up_interruptible(&up->port.state->port.delta_msr_wait);
}