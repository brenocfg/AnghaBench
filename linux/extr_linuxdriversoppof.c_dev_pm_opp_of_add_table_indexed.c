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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int _of_add_opp_table_v2 (struct device*,struct device_node*) ; 
 struct device_node* _opp_of_get_opp_desc_node (int /*<<< orphan*/ ,int) ; 
 int of_count_phandle_with_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int dev_pm_opp_of_add_table_indexed(struct device *dev, int index)
{
	struct device_node *opp_np;
	int ret, count;

again:
	opp_np = _opp_of_get_opp_desc_node(dev->of_node, index);
	if (!opp_np) {
		/*
		 * If only one phandle is present, then the same OPP table
		 * applies for all index requests.
		 */
		count = of_count_phandle_with_args(dev->of_node,
						   "operating-points-v2", NULL);
		if (count == 1 && index) {
			index = 0;
			goto again;
		}

		return -ENODEV;
	}

	ret = _of_add_opp_table_v2(dev, opp_np);
	of_node_put(opp_np);

	return ret;
}