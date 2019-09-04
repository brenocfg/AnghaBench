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
struct sirfsoc_uart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 

__attribute__((used)) static void sirfsoc_uart_pm(struct uart_port *port, unsigned int state,
			      unsigned int oldstate)
{
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	if (!state)
		clk_prepare_enable(sirfport->clk);
	else
		clk_disable_unprepare(sirfport->clk);
}