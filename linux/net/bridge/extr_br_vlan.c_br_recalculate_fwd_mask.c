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
struct net_bridge {scalar_t__ vlan_proto; unsigned int group_fwd_mask_required; unsigned int* group_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_ENABLED ; 
 unsigned int BR_GROUPFWD_8021AD ; 
 unsigned int BR_GROUPFWD_DEFAULT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

void br_recalculate_fwd_mask(struct net_bridge *br)
{
	if (!br_opt_get(br, BROPT_VLAN_ENABLED) ||
	    br->vlan_proto == htons(ETH_P_8021Q))
		br->group_fwd_mask_required = BR_GROUPFWD_DEFAULT;
	else /* vlan_enabled && ETH_P_8021AD */
		br->group_fwd_mask_required = BR_GROUPFWD_8021AD &
					      ~(1u << br->group_addr[5]);
}