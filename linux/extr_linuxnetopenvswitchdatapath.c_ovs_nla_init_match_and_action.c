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
struct sw_flow_match {int /*<<< orphan*/ * mask; } ;
struct sw_flow_mask {int dummy; } ;
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sw_flow_actions*) ; 
 size_t OVS_FLOW_ATTR_ACTIONS ; 
 size_t OVS_FLOW_ATTR_KEY ; 
 size_t OVS_FLOW_ATTR_MASK ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*) ; 
 int PTR_ERR (struct sw_flow_actions*) ; 
 struct sw_flow_actions* get_flow_actions (struct net*,struct nlattr*,struct sw_flow_key*,struct sw_flow_mask*,int) ; 
 int /*<<< orphan*/  ovs_match_init (struct sw_flow_match*,struct sw_flow_key*,int,struct sw_flow_mask*) ; 
 int ovs_nla_get_match (struct net*,struct sw_flow_match*,struct nlattr*,struct nlattr*,int) ; 

__attribute__((used)) static int ovs_nla_init_match_and_action(struct net *net,
					 struct sw_flow_match *match,
					 struct sw_flow_key *key,
					 struct nlattr **a,
					 struct sw_flow_actions **acts,
					 bool log)
{
	struct sw_flow_mask mask;
	int error = 0;

	if (a[OVS_FLOW_ATTR_KEY]) {
		ovs_match_init(match, key, true, &mask);
		error = ovs_nla_get_match(net, match, a[OVS_FLOW_ATTR_KEY],
					  a[OVS_FLOW_ATTR_MASK], log);
		if (error)
			goto error;
	}

	if (a[OVS_FLOW_ATTR_ACTIONS]) {
		if (!a[OVS_FLOW_ATTR_KEY]) {
			OVS_NLERR(log,
				  "Flow key attribute not present in set flow.");
			error = -EINVAL;
			goto error;
		}

		*acts = get_flow_actions(net, a[OVS_FLOW_ATTR_ACTIONS], key,
					 &mask, log);
		if (IS_ERR(*acts)) {
			error = PTR_ERR(*acts);
			goto error;
		}
	}

	/* On success, error is 0. */
error:
	match->mask = NULL;
	return error;
}