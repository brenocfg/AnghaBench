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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nf_hook_state {int dummy; } ;
struct nf_hook_ops {scalar_t__ priority; } ;
struct nf_hook_entries {unsigned int num_hook_entries; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hooks_bridge; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 scalar_t__ NF_BR_PRI_BRNF ; 
 struct nf_hook_ops** nf_hook_entries_get_hook_ops (struct nf_hook_entries const*) ; 
 int nf_hook_slow (struct sk_buff*,struct nf_hook_state*,struct nf_hook_entries const*,unsigned int) ; 
 int /*<<< orphan*/  nf_hook_state_init (struct nf_hook_state*,unsigned int,int /*<<< orphan*/ ,struct net_device*,struct net_device*,struct sock*,struct net*,int (*) (struct net*,struct sock*,struct sk_buff*)) ; 
 struct nf_hook_entries* rcu_dereference (int /*<<< orphan*/ ) ; 

int br_nf_hook_thresh(unsigned int hook, struct net *net,
		      struct sock *sk, struct sk_buff *skb,
		      struct net_device *indev,
		      struct net_device *outdev,
		      int (*okfn)(struct net *, struct sock *,
				  struct sk_buff *))
{
	const struct nf_hook_entries *e;
	struct nf_hook_state state;
	struct nf_hook_ops **ops;
	unsigned int i;
	int ret;

	e = rcu_dereference(net->nf.hooks_bridge[hook]);
	if (!e)
		return okfn(net, sk, skb);

	ops = nf_hook_entries_get_hook_ops(e);
	for (i = 0; i < e->num_hook_entries &&
	      ops[i]->priority <= NF_BR_PRI_BRNF; i++)
		;

	nf_hook_state_init(&state, hook, NFPROTO_BRIDGE, indev, outdev,
			   sk, net, okfn);

	ret = nf_hook_slow(skb, &state, e, i);
	if (ret == 1)
		ret = okfn(net, sk, skb);

	return ret;
}