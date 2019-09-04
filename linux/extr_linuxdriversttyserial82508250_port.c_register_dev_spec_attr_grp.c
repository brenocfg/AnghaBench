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
struct TYPE_2__ {size_t type; int /*<<< orphan*/ * attr_group; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial8250_config {scalar_t__* rxtrig_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_dev_attr_group ; 
 struct serial8250_config* uart_config ; 

__attribute__((used)) static void register_dev_spec_attr_grp(struct uart_8250_port *up)
{
	const struct serial8250_config *conf_type = &uart_config[up->port.type];

	if (conf_type->rxtrig_bytes[0])
		up->port.attr_group = &serial8250_dev_attr_group;
}