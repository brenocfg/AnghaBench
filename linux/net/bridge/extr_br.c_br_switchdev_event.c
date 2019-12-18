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
struct switchdev_notifier_fdb_info {int offloaded; int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  SWITCHDEV_FDB_ADD_TO_BRIDGE 130 
#define  SWITCHDEV_FDB_DEL_TO_BRIDGE 129 
#define  SWITCHDEV_FDB_OFFLOADED 128 
 int br_fdb_external_learn_add (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int br_fdb_external_learn_del (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_fdb_offloaded_set (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct net_bridge_port* br_port_get_rtnl_rcu (struct net_device*) ; 
 int notifier_from_errno (int) ; 
 struct net_device* switchdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int br_switchdev_event(struct notifier_block *unused,
			      unsigned long event, void *ptr)
{
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	struct net_bridge_port *p;
	struct net_bridge *br;
	struct switchdev_notifier_fdb_info *fdb_info;
	int err = NOTIFY_DONE;

	p = br_port_get_rtnl_rcu(dev);
	if (!p)
		goto out;

	br = p->br;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_BRIDGE:
		fdb_info = ptr;
		err = br_fdb_external_learn_add(br, p, fdb_info->addr,
						fdb_info->vid, false);
		if (err) {
			err = notifier_from_errno(err);
			break;
		}
		br_fdb_offloaded_set(br, p, fdb_info->addr,
				     fdb_info->vid, true);
		break;
	case SWITCHDEV_FDB_DEL_TO_BRIDGE:
		fdb_info = ptr;
		err = br_fdb_external_learn_del(br, p, fdb_info->addr,
						fdb_info->vid, false);
		if (err)
			err = notifier_from_errno(err);
		break;
	case SWITCHDEV_FDB_OFFLOADED:
		fdb_info = ptr;
		br_fdb_offloaded_set(br, p, fdb_info->addr,
				     fdb_info->vid, fdb_info->offloaded);
		break;
	}

out:
	return err;
}