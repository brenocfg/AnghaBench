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
struct sample_arg {scalar_t__ probability; int /*<<< orphan*/  exec; } ;
typedef  struct nlattr const nlattr ;
struct datapath {int dummy; } ;

/* Variables and functions */
 scalar_t__ U32_MAX ; 
 int clone_execute (struct datapath*,struct sk_buff*,struct sw_flow_key*,int /*<<< orphan*/ ,struct nlattr const*,int,int,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 void* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 struct nlattr const* nla_next (struct nlattr const*,int*) ; 
 scalar_t__ prandom_u32 () ; 

__attribute__((used)) static int sample(struct datapath *dp, struct sk_buff *skb,
		  struct sw_flow_key *key, const struct nlattr *attr,
		  bool last)
{
	struct nlattr *actions;
	struct nlattr *sample_arg;
	int rem = nla_len(attr);
	const struct sample_arg *arg;
	bool clone_flow_key;

	/* The first action is always 'OVS_SAMPLE_ATTR_ARG'. */
	sample_arg = nla_data(attr);
	arg = nla_data(sample_arg);
	actions = nla_next(sample_arg, &rem);

	if ((arg->probability != U32_MAX) &&
	    (!arg->probability || prandom_u32() > arg->probability)) {
		if (last)
			consume_skb(skb);
		return 0;
	}

	clone_flow_key = !arg->exec;
	return clone_execute(dp, skb, key, 0, actions, rem, last,
			     clone_flow_key);
}