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
struct ioc4_port {int ip_flags; struct uart_port* ip_port; } ;

/* Variables and functions */
 int PORT_ACTIVE ; 

__attribute__((used)) static inline int port_is_active(struct ioc4_port *port,
		struct uart_port *uart_port)
{
	if (port) {
		if ((port->ip_flags & PORT_ACTIVE)
					&& (port->ip_port == uart_port))
			return 1;
	}
	return 0;
}