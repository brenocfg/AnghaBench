#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int line; } ;
struct asc_port {int /*<<< orphan*/ * rts; TYPE_1__ port; void* force_m1; void* hw_flow_control; } ;

/* Variables and functions */
 int ASC_MAX_PORTS ; 
 char* ASC_SERIAL_NAME ; 
 scalar_t__ WARN_ON (int) ; 
 struct asc_port* asc_ports ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static struct asc_port *asc_of_get_asc_port(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int id;

	if (!np)
		return NULL;

	id = of_alias_get_id(np, "serial");
	if (id < 0)
		id = of_alias_get_id(np, ASC_SERIAL_NAME);

	if (id < 0)
		id = 0;

	if (WARN_ON(id >= ASC_MAX_PORTS))
		return NULL;

	asc_ports[id].hw_flow_control = of_property_read_bool(np,
							"uart-has-rtscts");
	asc_ports[id].force_m1 =  of_property_read_bool(np, "st,force_m1");
	asc_ports[id].port.line = id;
	asc_ports[id].rts = NULL;

	return &asc_ports[id];
}