#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tci; } ;
struct TYPE_4__ {TYPE_1__ vlan; int /*<<< orphan*/  type; } ;
struct sw_flow_key {TYPE_2__ eth; } ;
struct sw_flow_actions {int /*<<< orphan*/  orig_len; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sw_flow_actions*) ; 
 int /*<<< orphan*/  MAX_ACTIONS_BUFSIZE ; 
 int PTR_ERR (struct sw_flow_actions*) ; 
 int __ovs_nla_copy_actions (struct net*,struct nlattr const*,struct sw_flow_key const*,struct sw_flow_actions**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sw_flow_actions* nla_alloc_flow_actions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  ovs_nla_free_flow_actions (struct sw_flow_actions*) ; 

int ovs_nla_copy_actions(struct net *net, const struct nlattr *attr,
			 const struct sw_flow_key *key,
			 struct sw_flow_actions **sfa, bool log)
{
	int err;

	*sfa = nla_alloc_flow_actions(min(nla_len(attr), MAX_ACTIONS_BUFSIZE));
	if (IS_ERR(*sfa))
		return PTR_ERR(*sfa);

	(*sfa)->orig_len = nla_len(attr);
	err = __ovs_nla_copy_actions(net, attr, key, sfa, key->eth.type,
				     key->eth.vlan.tci, log);
	if (err)
		ovs_nla_free_flow_actions(*sfa);

	return err;
}