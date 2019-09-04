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
typedef  void* u32 ;
struct sw_flow_key {void* recirc_id; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct deferred_action {struct sw_flow_key pkt_key; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct deferred_action* add_deferred_actions (struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 struct sw_flow_key* clone_key (struct sw_flow_key*) ; 
 int do_execute_actions (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 int /*<<< orphan*/  exec_actions_level ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  ovs_dp_name (struct datapath*) ; 
 int /*<<< orphan*/  ovs_dp_process_packet (struct sk_buff*,struct sw_flow_key*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clone_execute(struct datapath *dp, struct sk_buff *skb,
			 struct sw_flow_key *key, u32 recirc_id,
			 const struct nlattr *actions, int len,
			 bool last, bool clone_flow_key)
{
	struct deferred_action *da;
	struct sw_flow_key *clone;

	skb = last ? skb : skb_clone(skb, GFP_ATOMIC);
	if (!skb) {
		/* Out of memory, skip this action.
		 */
		return 0;
	}

	/* When clone_flow_key is false, the 'key' will not be change
	 * by the actions, then the 'key' can be used directly.
	 * Otherwise, try to clone key from the next recursion level of
	 * 'flow_keys'. If clone is successful, execute the actions
	 * without deferring.
	 */
	clone = clone_flow_key ? clone_key(key) : key;
	if (clone) {
		int err = 0;

		if (actions) { /* Sample action */
			if (clone_flow_key)
				__this_cpu_inc(exec_actions_level);

			err = do_execute_actions(dp, skb, clone,
						 actions, len);

			if (clone_flow_key)
				__this_cpu_dec(exec_actions_level);
		} else { /* Recirc action */
			clone->recirc_id = recirc_id;
			ovs_dp_process_packet(skb, clone);
		}
		return err;
	}

	/* Out of 'flow_keys' space. Defer actions */
	da = add_deferred_actions(skb, key, actions, len);
	if (da) {
		if (!actions) { /* Recirc action */
			key = &da->pkt_key;
			key->recirc_id = recirc_id;
		}
	} else {
		/* Out of per CPU action FIFO space. Drop the 'skb' and
		 * log an error.
		 */
		kfree_skb(skb);

		if (net_ratelimit()) {
			if (actions) { /* Sample action */
				pr_warn("%s: deferred action limit reached, drop sample action\n",
					ovs_dp_name(dp));
			} else {  /* Recirc action */
				pr_warn("%s: deferred action limit reached, drop recirc action\n",
					ovs_dp_name(dp));
			}
		}
	}
	return 0;
}