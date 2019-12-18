#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vport {int /*<<< orphan*/  rcu; TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ reg_state; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (TYPE_1__*) ; 
 scalar_t__ netif_is_ovs_port (TYPE_1__*) ; 
 int /*<<< orphan*/  ovs_netdev_detach_dev (struct vport*) ; 
 int /*<<< orphan*/  rtnl_delete_link (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  vport_netdev_free ; 

void ovs_netdev_tunnel_destroy(struct vport *vport)
{
	rtnl_lock();
	if (netif_is_ovs_port(vport->dev))
		ovs_netdev_detach_dev(vport);

	/* We can be invoked by both explicit vport deletion and
	 * underlying netdev deregistration; delete the link only
	 * if it's not already shutting down.
	 */
	if (vport->dev->reg_state == NETREG_REGISTERED)
		rtnl_delete_link(vport->dev);
	dev_put(vport->dev);
	vport->dev = NULL;
	rtnl_unlock();

	call_rcu(&vport->rcu, vport_netdev_free);
}