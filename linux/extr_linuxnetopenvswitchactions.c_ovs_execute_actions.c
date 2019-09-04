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
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int /*<<< orphan*/  actions_len; int /*<<< orphan*/  actions; int /*<<< orphan*/  orig_len; } ;
struct sk_buff {int dummy; } ;
struct datapath {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  acts_origlen; } ;

/* Variables and functions */
 int ENETDOWN ; 
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int OVS_RECURSION_LIMIT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int do_execute_actions (struct datapath*,struct sk_buff*,struct sw_flow_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_actions_level ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_crit_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_name (struct datapath*) ; 
 int /*<<< orphan*/  process_deferred_actions (struct datapath*) ; 
 scalar_t__ unlikely (int) ; 

int ovs_execute_actions(struct datapath *dp, struct sk_buff *skb,
			const struct sw_flow_actions *acts,
			struct sw_flow_key *key)
{
	int err, level;

	level = __this_cpu_inc_return(exec_actions_level);
	if (unlikely(level > OVS_RECURSION_LIMIT)) {
		net_crit_ratelimited("ovs: recursion limit reached on datapath %s, probable configuration error\n",
				     ovs_dp_name(dp));
		kfree_skb(skb);
		err = -ENETDOWN;
		goto out;
	}

	OVS_CB(skb)->acts_origlen = acts->orig_len;
	err = do_execute_actions(dp, skb, key,
				 acts->actions, acts->actions_len);

	if (level == 1)
		process_deferred_actions(dp);

out:
	__this_cpu_dec(exec_actions_level);
	return err;
}