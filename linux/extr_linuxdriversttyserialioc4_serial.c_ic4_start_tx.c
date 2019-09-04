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
struct ioc4_port {TYPE_1__* ip_hooks; } ;
struct TYPE_2__ {int /*<<< orphan*/  intr_tx_mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_OUTPUT_LOWAT ; 
 int /*<<< orphan*/  enable_intrs (struct ioc4_port*,int /*<<< orphan*/ ) ; 
 struct ioc4_port* get_ioc4_port (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ port_is_active (struct ioc4_port*,struct uart_port*) ; 
 int /*<<< orphan*/  set_notification (struct ioc4_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ic4_start_tx(struct uart_port *the_port)
{
	struct ioc4_port *port = get_ioc4_port(the_port, 0);

	if (port_is_active(port, the_port)) {
		set_notification(port, N_OUTPUT_LOWAT, 1);
		enable_intrs(port, port->ip_hooks->intr_tx_mt);
	}
}