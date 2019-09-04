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
struct TYPE_2__ {struct device_node* of_node; } ;
struct regulator_dev {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct regulator_dev* of_find_regulator_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 

struct regulator_dev *of_parse_coupled_regulator(struct regulator_dev *rdev,
						 int index)
{
	struct device_node *node = rdev->dev.of_node;
	struct device_node *c_node;
	struct regulator_dev *c_rdev;

	c_node = of_parse_phandle(node, "regulator-coupled-with", index);
	if (!c_node)
		return NULL;

	c_rdev = of_find_regulator_by_node(c_node);

	of_node_put(c_node);

	return c_rdev;
}