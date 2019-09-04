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
struct atmel_uart_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CSR ; 
 unsigned int ATMEL_US_CTS ; 
 unsigned int ATMEL_US_DCD ; 
 unsigned int ATMEL_US_DSR ; 
 unsigned int ATMEL_US_RI ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 unsigned int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_get (int /*<<< orphan*/ ,unsigned int*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static u_int atmel_get_mctrl(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int ret = 0, status;

	status = atmel_uart_readl(port, ATMEL_US_CSR);

	/*
	 * The control signals are active low.
	 */
	if (!(status & ATMEL_US_DCD))
		ret |= TIOCM_CD;
	if (!(status & ATMEL_US_CTS))
		ret |= TIOCM_CTS;
	if (!(status & ATMEL_US_DSR))
		ret |= TIOCM_DSR;
	if (!(status & ATMEL_US_RI))
		ret |= TIOCM_RI;

	return mctrl_gpio_get(atmel_port->gpios, &ret);
}