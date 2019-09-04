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
struct imx_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 unsigned int imx_uart_get_hwmctrl (struct imx_port*) ; 
 int /*<<< orphan*/  mctrl_gpio_get (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int imx_uart_get_mctrl(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned int ret = imx_uart_get_hwmctrl(sport);

	mctrl_gpio_get(sport->gpios, &ret);

	return ret;
}