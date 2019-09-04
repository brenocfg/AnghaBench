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
struct uart_port {int dummy; } ;
struct tegra_uart_port {scalar_t__ enable_modem_interrupt; } ;

/* Variables and functions */
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static unsigned int tegra_uart_get_mctrl(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);

	/*
	 * RI - Ring detector is active
	 * CD/DCD/CAR - Carrier detect is always active. For some reason
	 *	linux has different names for carrier detect.
	 * DSR - Data Set ready is active as the hardware doesn't support it.
	 *	Don't know if the linux support this yet?
	 * CTS - Clear to send. Always set to active, as the hardware handles
	 *	CTS automatically.
	 */
	if (tup->enable_modem_interrupt)
		return TIOCM_RI | TIOCM_CD | TIOCM_DSR | TIOCM_CTS;
	return TIOCM_CTS;
}