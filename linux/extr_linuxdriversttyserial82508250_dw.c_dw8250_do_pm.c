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
struct uart_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_do_pm (struct uart_port*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
dw8250_do_pm(struct uart_port *port, unsigned int state, unsigned int old)
{
	if (!state)
		pm_runtime_get_sync(port->dev);

	serial8250_do_pm(port, state, old);

	if (state)
		pm_runtime_put_sync_suspend(port->dev);
}