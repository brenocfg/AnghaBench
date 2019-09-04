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
struct uart_port {int /*<<< orphan*/  membase; } ;
struct efm32_uart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct efm32_uart_port* to_efm_port (struct uart_port*) ; 

__attribute__((used)) static void efm32_uart_release_port(struct uart_port *port)
{
	struct efm32_uart_port *efm_port = to_efm_port(port);

	clk_unprepare(efm_port->clk);
	clk_put(efm_port->clk);
	iounmap(port->membase);
}