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
struct TYPE_2__ {int flags; } ;
struct uart_port {TYPE_1__ rs485; scalar_t__ rs485_config; } ;

/* Variables and functions */
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  uart_clear_mctrl (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_set_mctrl (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void uart_port_dtr_rts(struct uart_port *uport, int raise)
{
	int rs485_on = uport->rs485_config &&
		(uport->rs485.flags & SER_RS485_ENABLED);
	int RTS_after_send = !!(uport->rs485.flags & SER_RS485_RTS_AFTER_SEND);

	if (raise) {
		if (rs485_on && !RTS_after_send) {
			uart_set_mctrl(uport, TIOCM_DTR);
			uart_clear_mctrl(uport, TIOCM_RTS);
		} else {
			uart_set_mctrl(uport, TIOCM_DTR | TIOCM_RTS);
		}
	} else {
		unsigned int clear = TIOCM_DTR;

		clear |= (!rs485_on || !RTS_after_send) ? TIOCM_RTS : 0;
		uart_clear_mctrl(uport, clear);
	}
}