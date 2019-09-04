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
struct TYPE_2__ {int /*<<< orphan*/  (* stop_rx ) (struct uart_port*) ;} ;

/* Variables and functions */
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 

__attribute__((used)) static void
mpc52xx_uart_stop_rx(struct uart_port *port)
{
	/* port->lock taken by caller */
	psc_ops->stop_rx(port);
}