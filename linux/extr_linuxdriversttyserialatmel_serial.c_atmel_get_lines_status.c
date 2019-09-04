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
struct atmel_uart_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CSR ; 
 unsigned int ATMEL_US_CTS ; 
 unsigned int ATMEL_US_DCD ; 
 unsigned int ATMEL_US_DSR ; 
 unsigned int ATMEL_US_RI ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 int /*<<< orphan*/  UART_GPIO_CTS ; 
 int /*<<< orphan*/  UART_GPIO_DCD ; 
 int /*<<< orphan*/  UART_GPIO_DSR ; 
 int /*<<< orphan*/  UART_GPIO_RI ; 
 unsigned int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_get (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mctrl_gpio_to_gpiod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int atmel_get_lines_status(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	unsigned int status, ret = 0;

	status = atmel_uart_readl(port, ATMEL_US_CSR);

	mctrl_gpio_get(atmel_port->gpios, &ret);

	if (!IS_ERR_OR_NULL(mctrl_gpio_to_gpiod(atmel_port->gpios,
						UART_GPIO_CTS))) {
		if (ret & TIOCM_CTS)
			status &= ~ATMEL_US_CTS;
		else
			status |= ATMEL_US_CTS;
	}

	if (!IS_ERR_OR_NULL(mctrl_gpio_to_gpiod(atmel_port->gpios,
						UART_GPIO_DSR))) {
		if (ret & TIOCM_DSR)
			status &= ~ATMEL_US_DSR;
		else
			status |= ATMEL_US_DSR;
	}

	if (!IS_ERR_OR_NULL(mctrl_gpio_to_gpiod(atmel_port->gpios,
						UART_GPIO_RI))) {
		if (ret & TIOCM_RI)
			status &= ~ATMEL_US_RI;
		else
			status |= ATMEL_US_RI;
	}

	if (!IS_ERR_OR_NULL(mctrl_gpio_to_gpiod(atmel_port->gpios,
						UART_GPIO_DCD))) {
		if (ret & TIOCM_CD)
			status &= ~ATMEL_US_DCD;
		else
			status |= ATMEL_US_DCD;
	}

	return status;
}