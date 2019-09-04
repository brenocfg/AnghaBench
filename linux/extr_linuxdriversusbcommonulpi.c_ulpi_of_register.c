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
struct TYPE_4__ {struct device_node* of_node; struct device* parent; } ;
struct ulpi {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct device {TYPE_1__* parent; scalar_t__ of_node; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 struct device_node* of_get_child_by_name (scalar_t__,char*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int ulpi_of_register(struct ulpi *ulpi)
{
	struct device_node *np = NULL, *child;
	struct device *parent;

	/* Find a ulpi bus underneath the parent or the grandparent */
	parent = ulpi->dev.parent;
	if (parent->of_node)
		np = of_get_child_by_name(parent->of_node, "ulpi");
	else if (parent->parent && parent->parent->of_node)
		np = of_get_child_by_name(parent->parent->of_node, "ulpi");
	if (!np)
		return 0;

	child = of_get_next_available_child(np, NULL);
	of_node_put(np);
	if (!child)
		return -EINVAL;

	ulpi->dev.of_node = child;

	return 0;
}