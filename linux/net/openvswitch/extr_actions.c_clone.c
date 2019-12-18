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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int clone_execute (struct datapath*,struct sk_buff*,struct sw_flow_key*,int /*<<< orphan*/ ,struct nlattr*,int,int,int) ; 
 struct nlattr* nla_data (struct nlattr const*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr const*) ; 
 struct nlattr* nla_next (struct nlattr*,int*) ; 

__attribute__((used)) static int clone(struct datapath *dp, struct sk_buff *skb,
		 struct sw_flow_key *key, const struct nlattr *attr,
		 bool last)
{
	struct nlattr *actions;
	struct nlattr *clone_arg;
	int rem = nla_len(attr);
	bool dont_clone_flow_key;

	/* The first action is always 'OVS_CLONE_ATTR_ARG'. */
	clone_arg = nla_data(attr);
	dont_clone_flow_key = nla_get_u32(clone_arg);
	actions = nla_next(clone_arg, &rem);

	return clone_execute(dp, skb, key, 0, actions, rem, last,
			     !dont_clone_flow_key);
}