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
struct deferred_action {int actions_len; struct sw_flow_key pkt_key; struct nlattr const* actions; struct sk_buff* skb; } ;
struct action_fifo {int dummy; } ;

/* Variables and functions */
 struct deferred_action* action_fifo_put (struct action_fifo*) ; 
 int /*<<< orphan*/  action_fifos ; 
 struct action_fifo* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct deferred_action *add_deferred_actions(struct sk_buff *skb,
				    const struct sw_flow_key *key,
				    const struct nlattr *actions,
				    const int actions_len)
{
	struct action_fifo *fifo;
	struct deferred_action *da;

	fifo = this_cpu_ptr(action_fifos);
	da = action_fifo_put(fifo);
	if (da) {
		da->skb = skb;
		da->actions = actions;
		da->actions_len = actions_len;
		da->pkt_key = *key;
	}

	return da;
}