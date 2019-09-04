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
struct switchdev_trans {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
struct TYPE_2__ {int (* port_vlan_filtering ) (struct dsa_switch*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

int dsa_port_vlan_filtering(struct dsa_port *dp, bool vlan_filtering,
			    struct switchdev_trans *trans)
{
	struct dsa_switch *ds = dp->ds;

	/* bridge skips -EOPNOTSUPP, so skip the prepare phase */
	if (switchdev_trans_ph_prepare(trans))
		return 0;

	if (ds->ops->port_vlan_filtering)
		return ds->ops->port_vlan_filtering(ds, dp->index,
						    vlan_filtering);

	return 0;
}