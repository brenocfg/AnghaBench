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
struct netdev_phys_item_id {int id_len; int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;
struct dsa_switch_tree {int /*<<< orphan*/  index; } ;
struct dsa_switch {scalar_t__ devlink; struct dsa_switch_tree* dst; } ;
struct dsa_port {struct dsa_switch* ds; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dsa_slave_get_port_parent_id(struct net_device *dev,
					struct netdev_phys_item_id *ppid)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;
	struct dsa_switch_tree *dst = ds->dst;

	/* For non-legacy ports, devlink is used and it takes
	 * care of the name generation. This ndo implementation
	 * should be removed with legacy support.
	 */
	if (dp->ds->devlink)
		return -EOPNOTSUPP;

	ppid->id_len = sizeof(dst->index);
	memcpy(&ppid->id, &dst->index, ppid->id_len);

	return 0;
}