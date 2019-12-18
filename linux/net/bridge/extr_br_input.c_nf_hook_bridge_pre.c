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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct nf_hook_state {int dummy; } ;
struct nf_hook_entries {unsigned int num_hook_entries; int /*<<< orphan*/ * hooks; } ;
struct TYPE_3__ {int /*<<< orphan*/ * hooks_bridge; } ;
struct net {TYPE_1__ nf; } ;
struct TYPE_4__ {int /*<<< orphan*/  br_netfilter_broute; } ;

/* Variables and functions */
 TYPE_2__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 size_t NFPROTO_BRIDGE ; 
#define  NF_ACCEPT 130 
 size_t NF_BR_PRE_ROUTING ; 
#define  NF_DROP 129 
#define  NF_QUEUE 128 
 unsigned int NF_VERDICT_MASK ; 
 int RX_HANDLER_CONSUMED ; 
 int RX_HANDLER_PASS ; 
 int /*<<< orphan*/  br_handle_frame_finish (struct net*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int nf_hook_entry_hookfn (int /*<<< orphan*/ *,struct sk_buff*,struct nf_hook_state*) ; 
 int /*<<< orphan*/  nf_hook_state_init (struct nf_hook_state*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct net*,int /*<<< orphan*/  (*) (struct net*,int /*<<< orphan*/ *,struct sk_buff*)) ; 
 int /*<<< orphan*/ ** nf_hooks_needed ; 
 int nf_queue (struct sk_buff*,struct nf_hook_state*,unsigned int,unsigned int) ; 
 struct nf_hook_entries* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nf_hook_bridge_pre(struct sk_buff *skb, struct sk_buff **pskb)
{
#ifdef CONFIG_NETFILTER_FAMILY_BRIDGE
	struct nf_hook_entries *e = NULL;
	struct nf_hook_state state;
	unsigned int verdict, i;
	struct net *net;
	int ret;

	net = dev_net(skb->dev);
#ifdef HAVE_JUMP_LABEL
	if (!static_key_false(&nf_hooks_needed[NFPROTO_BRIDGE][NF_BR_PRE_ROUTING]))
		goto frame_finish;
#endif

	e = rcu_dereference(net->nf.hooks_bridge[NF_BR_PRE_ROUTING]);
	if (!e)
		goto frame_finish;

	nf_hook_state_init(&state, NF_BR_PRE_ROUTING,
			   NFPROTO_BRIDGE, skb->dev, NULL, NULL,
			   net, br_handle_frame_finish);

	for (i = 0; i < e->num_hook_entries; i++) {
		verdict = nf_hook_entry_hookfn(&e->hooks[i], skb, &state);
		switch (verdict & NF_VERDICT_MASK) {
		case NF_ACCEPT:
			if (BR_INPUT_SKB_CB(skb)->br_netfilter_broute) {
				*pskb = skb;
				return RX_HANDLER_PASS;
			}
			break;
		case NF_DROP:
			kfree_skb(skb);
			return RX_HANDLER_CONSUMED;
		case NF_QUEUE:
			ret = nf_queue(skb, &state, i, verdict);
			if (ret == 1)
				continue;
			return RX_HANDLER_CONSUMED;
		default: /* STOLEN */
			return RX_HANDLER_CONSUMED;
		}
	}
frame_finish:
	net = dev_net(skb->dev);
	br_handle_frame_finish(net, NULL, skb);
#else
	br_handle_frame_finish(dev_net(skb->dev), NULL, skb);
#endif
	return RX_HANDLER_CONSUMED;
}