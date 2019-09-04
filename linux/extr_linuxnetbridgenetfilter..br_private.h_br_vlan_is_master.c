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
struct net_bridge_vlan {int flags; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_MASTER ; 

__attribute__((used)) static inline bool br_vlan_is_master(const struct net_bridge_vlan *v)
{
	return v->flags & BRIDGE_VLAN_INFO_MASTER;
}