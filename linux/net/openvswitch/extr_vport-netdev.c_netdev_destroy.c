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
struct vport {int /*<<< orphan*/  rcu; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_is_ovs_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_netdev_detach_dev (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  vport_netdev_free ; 

__attribute__((used)) static void netdev_destroy(struct vport *vport)
{
	rtnl_lock();
	if (netif_is_ovs_port(vport->dev))
		ovs_netdev_detach_dev(vport);
	rtnl_unlock();

	call_rcu(&vport->rcu, vport_netdev_free);
}