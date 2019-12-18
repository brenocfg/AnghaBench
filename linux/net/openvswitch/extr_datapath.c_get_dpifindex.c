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
struct vport {TYPE_1__* dev; } ;
struct datapath {int dummy; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVSP_LOCAL ; 
 struct vport* ovs_vport_rcu (struct datapath const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int get_dpifindex(const struct datapath *dp)
{
	struct vport *local;
	int ifindex;

	rcu_read_lock();

	local = ovs_vport_rcu(dp, OVSP_LOCAL);
	if (local)
		ifindex = local->dev->ifindex;
	else
		ifindex = 0;

	rcu_read_unlock();

	return ifindex;
}