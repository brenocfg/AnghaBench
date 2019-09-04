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
typedef  int /*<<< orphan*/  u32 ;
struct opp_table {int /*<<< orphan*/  voltage_tolerance_v1; int /*<<< orphan*/  clock_latency_ns_max; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

void _of_init_opp_table(struct opp_table *opp_table, struct device *dev)
{
	struct device_node *np;

	/*
	 * Only required for backward compatibility with v1 bindings, but isn't
	 * harmful for other cases. And so we do it unconditionally.
	 */
	np = of_node_get(dev->of_node);
	if (np) {
		u32 val;

		if (!of_property_read_u32(np, "clock-latency", &val))
			opp_table->clock_latency_ns_max = val;
		of_property_read_u32(np, "voltage-tolerance",
				     &opp_table->voltage_tolerance_v1);
		of_node_put(np);
	}
}