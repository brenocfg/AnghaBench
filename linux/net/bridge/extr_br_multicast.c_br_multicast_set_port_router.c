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
struct net_bridge_port {unsigned long multicast_router; int /*<<< orphan*/  multicast_router_timer; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; scalar_t__ multicast_querier_interval; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MDB_RTR_TYPE_DISABLED 131 
#define  MDB_RTR_TYPE_PERM 130 
#define  MDB_RTR_TYPE_TEMP 129 
#define  MDB_RTR_TYPE_TEMP_QUERY 128 
 int /*<<< orphan*/  __del_port_router (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_add_router (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_mark_router (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int br_multicast_set_port_router(struct net_bridge_port *p, unsigned long val)
{
	struct net_bridge *br = p->br;
	unsigned long now = jiffies;
	int err = -EINVAL;

	spin_lock(&br->multicast_lock);
	if (p->multicast_router == val) {
		/* Refresh the temp router port timer */
		if (p->multicast_router == MDB_RTR_TYPE_TEMP)
			mod_timer(&p->multicast_router_timer,
				  now + br->multicast_querier_interval);
		err = 0;
		goto unlock;
	}
	switch (val) {
	case MDB_RTR_TYPE_DISABLED:
		p->multicast_router = MDB_RTR_TYPE_DISABLED;
		__del_port_router(p);
		del_timer(&p->multicast_router_timer);
		break;
	case MDB_RTR_TYPE_TEMP_QUERY:
		p->multicast_router = MDB_RTR_TYPE_TEMP_QUERY;
		__del_port_router(p);
		break;
	case MDB_RTR_TYPE_PERM:
		p->multicast_router = MDB_RTR_TYPE_PERM;
		del_timer(&p->multicast_router_timer);
		br_multicast_add_router(br, p);
		break;
	case MDB_RTR_TYPE_TEMP:
		p->multicast_router = MDB_RTR_TYPE_TEMP;
		br_multicast_mark_router(br, p);
		break;
	default:
		goto unlock;
	}
	err = 0;
unlock:
	spin_unlock(&br->multicast_lock);

	return err;
}