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
typedef  int u32 ;
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  exec ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NLA_HDRLEN ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_CLONE ; 
 int /*<<< orphan*/  OVS_CLONE_ATTR_EXEC ; 
 int __ovs_nla_copy_actions (struct net*,struct nlattr const*,struct sw_flow_key const*,struct sw_flow_actions**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  actions_may_change_flow (struct nlattr const*) ; 
 int /*<<< orphan*/  add_nested_action_end (struct sw_flow_actions*,int) ; 
 int add_nested_action_start (struct sw_flow_actions**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_len (struct nlattr const*) ; 
 int ovs_nla_add_action (struct sw_flow_actions**,int /*<<< orphan*/ ,int*,int,int) ; 

__attribute__((used)) static int validate_and_copy_clone(struct net *net,
				   const struct nlattr *attr,
				   const struct sw_flow_key *key,
				   struct sw_flow_actions **sfa,
				   __be16 eth_type, __be16 vlan_tci,
				   bool log, bool last)
{
	int start, err;
	u32 exec;

	if (nla_len(attr) && nla_len(attr) < NLA_HDRLEN)
		return -EINVAL;

	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_CLONE, log);
	if (start < 0)
		return start;

	exec = last || !actions_may_change_flow(attr);

	err = ovs_nla_add_action(sfa, OVS_CLONE_ATTR_EXEC, &exec,
				 sizeof(exec), log);
	if (err)
		return err;

	err = __ovs_nla_copy_actions(net, attr, key, sfa,
				     eth_type, vlan_tci, log);
	if (err)
		return err;

	add_nested_action_end(*sfa, start);

	return 0;
}