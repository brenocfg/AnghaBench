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
struct switch_dev {struct switch_dev* alias; struct switch_dev* name; int /*<<< orphan*/  vlan_ops; int /*<<< orphan*/  port_ops; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct switch_dev*) ; 
 scalar_t__ refcount ; 
 int /*<<< orphan*/  swlib_free_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swlib_free_port_map (struct switch_dev*) ; 
 int /*<<< orphan*/  swlib_priv_free () ; 

void
swlib_free(struct switch_dev *dev)
{
	swlib_free_attributes(&dev->ops);
	swlib_free_attributes(&dev->port_ops);
	swlib_free_attributes(&dev->vlan_ops);
	swlib_free_port_map(dev);
	free(dev->name);
	free(dev->alias);
	free(dev);

	if (--refcount == 0)
		swlib_priv_free();
}