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
struct xt_action_param {struct nf_hook_state* state; int /*<<< orphan*/  matchinfo; TYPE_1__* match; } ;
struct tcf_pkt_info {int dummy; } ;
struct tcf_ematch {int /*<<< orphan*/  net; scalar_t__ data; } ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ skb_iif; } ;
struct nf_hook_state {int dummy; } ;
struct net_device {int dummy; } ;
struct em_ipt_match {TYPE_1__* match; int /*<<< orphan*/  match_data; int /*<<< orphan*/  hook; } ;
struct TYPE_2__ {int (* match ) (struct sk_buff*,struct xt_action_param*) ;int /*<<< orphan*/  family; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nf_hook_state_init (struct nf_hook_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct sk_buff*,struct xt_action_param*) ; 

__attribute__((used)) static int em_ipt_match(struct sk_buff *skb, struct tcf_ematch *em,
			struct tcf_pkt_info *info)
{
	const struct em_ipt_match *im = (const void *)em->data;
	struct xt_action_param acpar = {};
	struct net_device *indev = NULL;
	struct nf_hook_state state;
	int ret;

	rcu_read_lock();

	if (skb->skb_iif)
		indev = dev_get_by_index_rcu(em->net, skb->skb_iif);

	nf_hook_state_init(&state, im->hook, im->match->family,
			   indev ?: skb->dev, skb->dev, NULL, em->net, NULL);

	acpar.match = im->match;
	acpar.matchinfo = im->match_data;
	acpar.state = &state;

	ret = im->match->match(skb, &acpar);

	rcu_read_unlock();
	return ret;
}