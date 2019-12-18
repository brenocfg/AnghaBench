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
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void vlan_tunnel_info_del(struct net_bridge_vlan_group *vg,
					struct net_bridge_vlan *vlan)
{
}