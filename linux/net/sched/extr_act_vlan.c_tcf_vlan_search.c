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
typedef  int /*<<< orphan*/  u32 ;
struct tc_action_net {int dummy; } ;
struct tc_action {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tc_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int tcf_idr_search (struct tc_action_net*,struct tc_action**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_net_id ; 

__attribute__((used)) static int tcf_vlan_search(struct net *net, struct tc_action **a, u32 index)
{
	struct tc_action_net *tn = net_generic(net, vlan_net_id);

	return tcf_idr_search(tn, a, index);
}