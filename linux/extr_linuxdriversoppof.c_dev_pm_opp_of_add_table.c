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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int _of_add_opp_table_v1 (struct device*) ; 
 int _of_add_opp_table_v2 (struct device*,struct device_node*) ; 
 struct device_node* dev_pm_opp_of_get_opp_desc_node (struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int dev_pm_opp_of_add_table(struct device *dev)
{
	struct device_node *opp_np;
	int ret;

	/*
	 * OPPs have two version of bindings now. The older one is deprecated,
	 * try for the new binding first.
	 */
	opp_np = dev_pm_opp_of_get_opp_desc_node(dev);
	if (!opp_np) {
		/*
		 * Try old-deprecated bindings for backward compatibility with
		 * older dtbs.
		 */
		return _of_add_opp_table_v1(dev);
	}

	ret = _of_add_opp_table_v2(dev, opp_np);
	of_node_put(opp_np);

	return ret;
}