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
struct fwtty_port {int mctrl; scalar_t__ break_ctl; } ;

/* Variables and functions */
 int OOB_RX_THROTTLE ; 
 unsigned int OOB_TX_THROTTLE ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int UART_LSR_BI ; 

__attribute__((used)) static unsigned int __fwtty_port_line_status(struct fwtty_port *port)
{
	unsigned int status = 0;

	/* TODO: add module param to tie RNG to DTR as well */

	if (port->mctrl & TIOCM_DTR)
		status |= TIOCM_DSR | TIOCM_CAR;
	if (port->mctrl & TIOCM_RTS)
		status |= TIOCM_CTS;
	if (port->mctrl & OOB_RX_THROTTLE)
		status |= OOB_TX_THROTTLE;
	/* emulate BRK as add'l line status */
	if (port->break_ctl)
		status |= UART_LSR_BI << 24;

	return status;
}