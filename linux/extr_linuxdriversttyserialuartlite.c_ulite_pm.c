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
struct uartlite_data {int /*<<< orphan*/  clk; } ;
struct uart_port {struct uartlite_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ulite_pm(struct uart_port *port, unsigned int state,
		     unsigned int oldstate)
{
	struct uartlite_data *pdata = port->private_data;

	if (!state)
		clk_enable(pdata->clk);
	else
		clk_disable(pdata->clk);
}