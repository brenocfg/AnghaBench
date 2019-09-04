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
struct vport {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (TYPE_1__*) ; 

__attribute__((used)) static void internal_dev_destroy(struct vport *vport)
{
	netif_stop_queue(vport->dev);
	rtnl_lock();
	dev_set_promiscuity(vport->dev, -1);

	/* unregister_netdevice() waits for an RCU grace period. */
	unregister_netdevice(vport->dev);
	free_percpu(vport->dev->tstats);
	rtnl_unlock();
}