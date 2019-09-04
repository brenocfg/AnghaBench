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
struct uart_port {int /*<<< orphan*/  type; } ;
struct sci_port {TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int UART_CONFIG_TYPE ; 
 int /*<<< orphan*/  sci_request_port (struct uart_port*) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE) {
		struct sci_port *sport = to_sci_port(port);

		port->type = sport->cfg->type;
		sci_request_port(port);
	}
}