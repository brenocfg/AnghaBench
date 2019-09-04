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
struct deferred_action {int actions_len; struct nlattr* actions; struct sw_flow_key pkt_key; struct sk_buff* skb; } ;
struct datapath {int dummy; } ;
struct action_fifo {int dummy; } ;

/* Variables and functions */
 struct deferred_action* action_fifo_get (struct action_fifo*) ; 
 int /*<<< orphan*/  action_fifo_init (struct action_fifo*) ; 
 scalar_t__ action_fifo_is_empty (struct action_fifo*) ; 
 int /*<<< orphan*/  action_fifos ; 
 int /*<<< orphan*/  do_execute_actions (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 int /*<<< orphan*/  ovs_dp_process_packet (struct sk_buff*,struct sw_flow_key*) ; 
 struct action_fifo* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_deferred_actions(struct datapath *dp)
{
	struct action_fifo *fifo = this_cpu_ptr(action_fifos);

	/* Do not touch the FIFO in case there is no deferred actions. */
	if (action_fifo_is_empty(fifo))
		return;

	/* Finishing executing all deferred actions. */
	do {
		struct deferred_action *da = action_fifo_get(fifo);
		struct sk_buff *skb = da->skb;
		struct sw_flow_key *key = &da->pkt_key;
		const struct nlattr *actions = da->actions;
		int actions_len = da->actions_len;

		if (actions)
			do_execute_actions(dp, skb, key, actions, actions_len);
		else
			ovs_dp_process_packet(skb, key);
	} while (!action_fifo_is_empty(fifo));

	/* Reset FIFO for the next packet.  */
	action_fifo_init(fifo);
}