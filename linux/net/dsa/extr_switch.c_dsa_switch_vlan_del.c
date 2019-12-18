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
struct dsa_switch {scalar_t__ index; TYPE_1__* ops; } ;
struct dsa_notifier_vlan_info {scalar_t__ sw_index; int /*<<< orphan*/  vlan; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int (* port_vlan_del ) (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_switch_vlan_del(struct dsa_switch *ds,
			       struct dsa_notifier_vlan_info *info)
{
	if (!ds->ops->port_vlan_del)
		return -EOPNOTSUPP;

	if (ds->index == info->sw_index)
		return ds->ops->port_vlan_del(ds, info->port, info->vlan);

	/* Do not deprogram the DSA links as they may be used as conduit
	 * for other VLAN members in the fabric.
	 */
	return 0;
}