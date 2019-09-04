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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct uart_pxa_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_PXA ; 

__attribute__((used)) static void serial_pxa_config_port(struct uart_port *port, int flags)
{
	struct uart_pxa_port *up = (struct uart_pxa_port *)port;
	up->port.type = PORT_PXA;
}