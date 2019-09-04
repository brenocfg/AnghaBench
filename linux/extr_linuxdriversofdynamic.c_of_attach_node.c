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
struct of_reconfig_data {struct device_node* dn; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  rd ;

/* Variables and functions */
 int /*<<< orphan*/  OF_RECONFIG_ATTACH_NODE ; 
 int /*<<< orphan*/  __of_attach_node (struct device_node*) ; 
 int /*<<< orphan*/  __of_attach_node_sysfs (struct device_node*) ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  memset (struct of_reconfig_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_mutex ; 
 int /*<<< orphan*/  of_reconfig_notify (int /*<<< orphan*/ ,struct of_reconfig_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int of_attach_node(struct device_node *np)
{
	struct of_reconfig_data rd;
	unsigned long flags;

	memset(&rd, 0, sizeof(rd));
	rd.dn = np;

	mutex_lock(&of_mutex);
	raw_spin_lock_irqsave(&devtree_lock, flags);
	__of_attach_node(np);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	__of_attach_node_sysfs(np);
	mutex_unlock(&of_mutex);

	of_reconfig_notify(OF_RECONFIG_ATTACH_NODE, &rd);

	return 0;
}