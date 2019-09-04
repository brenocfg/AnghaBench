#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imx_thermal_data {TYPE_1__* policy; int /*<<< orphan*/  cdev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_cooling_register (TYPE_1__*) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (TYPE_1__*) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_cpu_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_thermal_register_legacy_cooling(struct imx_thermal_data *data)
{
	struct device_node *np = of_get_cpu_node(data->policy->cpu, NULL);
	int ret;

	if (!np || !of_find_property(np, "#cooling-cells", NULL)) {
		data->cdev = cpufreq_cooling_register(data->policy);
		if (IS_ERR(data->cdev)) {
			ret = PTR_ERR(data->cdev);
			cpufreq_cpu_put(data->policy);
			return ret;
		}
	}

	return 0;
}