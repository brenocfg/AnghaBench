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
typedef  void* u32 ;
struct resource {int /*<<< orphan*/  flags; void* end; void* start; int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  IORESOURCE_BUS ; 
 int of_property_read_u32_array (struct device_node*,char*,void**,int /*<<< orphan*/ ) ; 

int of_pci_parse_bus_range(struct device_node *node, struct resource *res)
{
	u32 bus_range[2];
	int error;

	error = of_property_read_u32_array(node, "bus-range", bus_range,
					   ARRAY_SIZE(bus_range));
	if (error)
		return error;

	res->name = node->name;
	res->start = bus_range[0];
	res->end = bus_range[1];
	res->flags = IORESOURCE_BUS;

	return 0;
}