#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  vlan_id; TYPE_1__ addr; } ;
struct net_bridge_fdb_entry {int /*<<< orphan*/  offloaded; int /*<<< orphan*/  added_by_user; TYPE_3__* dst; TYPE_2__ key; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  RTM_DELNEIGH 129 
#define  RTM_NEWNEIGH 128 
 int /*<<< orphan*/  br_switchdev_fdb_call_notifiers (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
br_switchdev_fdb_notify(const struct net_bridge_fdb_entry *fdb, int type)
{
	if (!fdb->dst)
		return;

	switch (type) {
	case RTM_DELNEIGH:
		br_switchdev_fdb_call_notifiers(false, fdb->key.addr.addr,
						fdb->key.vlan_id,
						fdb->dst->dev,
						fdb->added_by_user,
						fdb->offloaded);
		break;
	case RTM_NEWNEIGH:
		br_switchdev_fdb_call_notifiers(true, fdb->key.addr.addr,
						fdb->key.vlan_id,
						fdb->dst->dev,
						fdb->added_by_user,
						fdb->offloaded);
		break;
	}
}