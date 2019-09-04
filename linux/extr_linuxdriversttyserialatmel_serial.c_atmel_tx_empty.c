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
typedef  int /*<<< orphan*/  u_int ;
struct uart_port {int dummy; } ;
struct atmel_uart_port {scalar_t__ tx_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CSR ; 
 int ATMEL_US_TXEMPTY ; 
 int /*<<< orphan*/  TIOCSER_TEMT ; 
 int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static u_int atmel_tx_empty(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_port->tx_stopped)
		return TIOCSER_TEMT;
	return (atmel_uart_readl(port, ATMEL_US_CSR) & ATMEL_US_TXEMPTY) ?
		TIOCSER_TEMT :
		0;
}