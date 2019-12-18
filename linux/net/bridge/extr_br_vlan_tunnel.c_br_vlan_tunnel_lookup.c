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
typedef  int /*<<< orphan*/  u64 ;
struct rhashtable {int dummy; } ;
struct net_bridge_vlan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_vlan_tunnel_rht_params ; 
 struct net_bridge_vlan* rhashtable_lookup_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_bridge_vlan *br_vlan_tunnel_lookup(struct rhashtable *tbl,
						     u64 tunnel_id)
{
	return rhashtable_lookup_fast(tbl, &tunnel_id,
				      br_vlan_tunnel_rht_params);
}