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
struct of_phandle_args {int args_count; int* args; TYPE_1__* np; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 

__attribute__((used)) static int qoriq_tmu_get_sensor_id(void)
{
	int ret, id;
	struct of_phandle_args sensor_specs;
	struct device_node *np, *sensor_np;

	np = of_find_node_by_name(NULL, "thermal-zones");
	if (!np)
		return -ENODEV;

	sensor_np = of_get_next_child(np, NULL);
	ret = of_parse_phandle_with_args(sensor_np, "thermal-sensors",
			"#thermal-sensor-cells",
			0, &sensor_specs);
	if (ret) {
		of_node_put(np);
		of_node_put(sensor_np);
		return ret;
	}

	if (sensor_specs.args_count >= 1) {
		id = sensor_specs.args[0];
		WARN(sensor_specs.args_count > 1,
				"%s: too many cells in sensor specifier %d\n",
				sensor_specs.np->name, sensor_specs.args_count);
	} else {
		id = 0;
	}

	of_node_put(np);
	of_node_put(sensor_np);

	return id;
}