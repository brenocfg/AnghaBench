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
struct net_bridge {scalar_t__ vlan_proto; int* group_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  vlan_enabled; scalar_t__ group_addr_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recalculate_group_addr(struct net_bridge *br)
{
	if (br->group_addr_set)
		return;

	spin_lock_bh(&br->lock);
	if (!br->vlan_enabled || br->vlan_proto == htons(ETH_P_8021Q)) {
		/* Bridge Group Address */
		br->group_addr[5] = 0x00;
	} else { /* vlan_enabled && ETH_P_8021AD */
		/* Provider Bridge Group Address */
		br->group_addr[5] = 0x08;
	}
	spin_unlock_bh(&br->lock);
}