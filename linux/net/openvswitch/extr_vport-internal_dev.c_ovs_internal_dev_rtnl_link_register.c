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

/* Variables and functions */
 int /*<<< orphan*/  internal_dev_link_ops ; 
 int /*<<< orphan*/  ovs_internal_vport_ops ; 
 int ovs_vport_ops_register (int /*<<< orphan*/ *) ; 
 int rtnl_link_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_link_unregister (int /*<<< orphan*/ *) ; 

int ovs_internal_dev_rtnl_link_register(void)
{
	int err;

	err = rtnl_link_register(&internal_dev_link_ops);
	if (err < 0)
		return err;

	err = ovs_vport_ops_register(&ovs_internal_vport_ops);
	if (err < 0)
		rtnl_link_unregister(&internal_dev_link_ops);

	return err;
}