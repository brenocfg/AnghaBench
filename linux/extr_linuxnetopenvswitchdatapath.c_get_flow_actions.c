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
struct sw_flow_mask {int dummy; } ;
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sw_flow_actions* ERR_PTR (int) ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*) ; 
 int /*<<< orphan*/  ovs_flow_mask_key (struct sw_flow_key*,struct sw_flow_key const*,int,struct sw_flow_mask const*) ; 
 int ovs_nla_copy_actions (struct net*,struct nlattr const*,struct sw_flow_key*,struct sw_flow_actions**,int) ; 

__attribute__((used)) static struct sw_flow_actions *get_flow_actions(struct net *net,
						const struct nlattr *a,
						const struct sw_flow_key *key,
						const struct sw_flow_mask *mask,
						bool log)
{
	struct sw_flow_actions *acts;
	struct sw_flow_key masked_key;
	int error;

	ovs_flow_mask_key(&masked_key, key, true, mask);
	error = ovs_nla_copy_actions(net, a, &masked_key, &acts, log);
	if (error) {
		OVS_NLERR(log,
			  "Actions may not be safe on all matching packets");
		return ERR_PTR(error);
	}

	return acts;
}