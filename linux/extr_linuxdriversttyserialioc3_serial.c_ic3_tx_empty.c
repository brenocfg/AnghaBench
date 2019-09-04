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
struct ioc3_port {TYPE_1__* ip_serial_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  shadow; } ;

/* Variables and functions */
 int SHADOW_TEMT ; 
 unsigned int TIOCSER_TEMT ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ic3_tx_empty(struct uart_port *the_port)
{
	unsigned int ret = 0;
	struct ioc3_port *port = get_ioc3_port(the_port);

	if (readl(&port->ip_serial_regs->shadow) & SHADOW_TEMT)
		ret = TIOCSER_TEMT;
	return ret;
}