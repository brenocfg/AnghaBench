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
typedef  scalar_t__ u16 ;
struct net_bridge_vlan_group {scalar_t__ pvid; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static bool __vlan_delete_pvid(struct net_bridge_vlan_group *vg, u16 vid)
{
	if (vg->pvid != vid)
		return false;

	smp_wmb();
	vg->pvid = 0;

	return true;
}