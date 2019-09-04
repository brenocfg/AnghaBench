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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc52xx_uart_driver ; 
 struct uart_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,struct uart_port*) ; 

__attribute__((used)) static int
mpc52xx_uart_of_remove(struct platform_device *op)
{
	struct uart_port *port = platform_get_drvdata(op);

	if (port)
		uart_remove_one_port(&mpc52xx_uart_driver, port);

	return 0;
}