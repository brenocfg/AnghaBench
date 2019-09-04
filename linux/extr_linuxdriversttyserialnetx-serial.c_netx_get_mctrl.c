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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int FR_CTS ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 scalar_t__ UART_FR ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int netx_get_mctrl(struct uart_port *port)
{
	unsigned int ret = TIOCM_DSR | TIOCM_CAR;

	if (readl(port->membase + UART_FR) & FR_CTS)
		ret |= TIOCM_CTS;

	return ret;
}