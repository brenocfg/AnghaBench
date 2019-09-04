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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct imx_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_IMX ; 
 int UART_CONFIG_TYPE ; 

__attribute__((used)) static void imx_uart_config_port(struct uart_port *port, int flags)
{
	struct imx_port *sport = (struct imx_port *)port;

	if (flags & UART_CONFIG_TYPE)
		sport->port.type = PORT_IMX;
}