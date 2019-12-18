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
struct net_device {int /*<<< orphan*/  mrp_port; } ;
struct mrp_port {int /*<<< orphan*/ * applicants; } ;

/* Variables and functions */
 unsigned int MRP_APPLICATION_MAX ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct mrp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct mrp_port* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mrp_release_port(struct net_device *dev)
{
	struct mrp_port *port = rtnl_dereference(dev->mrp_port);
	unsigned int i;

	for (i = 0; i <= MRP_APPLICATION_MAX; i++) {
		if (rtnl_dereference(port->applicants[i]))
			return;
	}
	RCU_INIT_POINTER(dev->mrp_port, NULL);
	kfree_rcu(port, rcu);
}