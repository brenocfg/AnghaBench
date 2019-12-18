#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tunnel_id; } ;
struct net_bridge_vlan {TYPE_1__ tinfo; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlan_tunid_inrange(struct net_bridge_vlan *v_curr,
			       struct net_bridge_vlan *v_last)
{
	__be32 tunid_curr = tunnel_id_to_key32(v_curr->tinfo.tunnel_id);
	__be32 tunid_last = tunnel_id_to_key32(v_last->tinfo.tunnel_id);

	return (be32_to_cpu(tunid_curr) - be32_to_cpu(tunid_last)) == 1;
}