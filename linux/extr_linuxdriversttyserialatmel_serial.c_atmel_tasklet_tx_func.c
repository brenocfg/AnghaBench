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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct atmel_uart_port {int /*<<< orphan*/  (* schedule_tx ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_tasklet_tx_func(unsigned long data)
{
	struct uart_port *port = (struct uart_port *)data;
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	/* The interrupt handler does not take the lock */
	spin_lock(&port->lock);
	atmel_port->schedule_tx(port);
	spin_unlock(&port->lock);
}