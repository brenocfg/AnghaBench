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
struct device_node {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  devtree_lock ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct device_node *of_get_parent(const struct device_node *node)
{
	struct device_node *np;
	unsigned long flags;

	if (!node)
		return NULL;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	np = of_node_get(node->parent);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	return np;
}