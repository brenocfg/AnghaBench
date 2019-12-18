#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; struct net* net; int /*<<< orphan*/  (* okfn ) (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ;int /*<<< orphan*/  hook; int /*<<< orphan*/  pf; } ;
struct nf_queue_entry {unsigned int hook_index; TYPE_1__ state; struct sk_buff* skb; } ;
struct nf_hook_entry {int dummy; } ;
struct nf_hook_entries {unsigned int num_hook_entries; struct nf_hook_entry* hooks; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  NF_ACCEPT 131 
 unsigned int NF_DROP ; 
#define  NF_QUEUE 130 
 unsigned int NF_REPEAT ; 
#define  NF_STOLEN 129 
#define  NF_STOP 128 
 unsigned int NF_VERDICT_MASK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct nf_hook_entries* nf_hook_entries_head (struct net const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nf_hook_entry_hookfn (struct nf_hook_entry const*,struct sk_buff*,TYPE_1__*) ; 
 unsigned int nf_iterate (struct sk_buff*,TYPE_1__*,struct nf_hook_entries const*,unsigned int*) ; 
 int nf_queue (struct sk_buff*,TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nf_queue_entry_release_refs (struct nf_queue_entry*) ; 
 scalar_t__ nf_reroute (struct sk_buff*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  stub1 (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 

void nf_reinject(struct nf_queue_entry *entry, unsigned int verdict)
{
	const struct nf_hook_entry *hook_entry;
	const struct nf_hook_entries *hooks;
	struct sk_buff *skb = entry->skb;
	const struct net *net;
	unsigned int i;
	int err;
	u8 pf;

	net = entry->state.net;
	pf = entry->state.pf;

	hooks = nf_hook_entries_head(net, pf, entry->state.hook);

	nf_queue_entry_release_refs(entry);

	i = entry->hook_index;
	if (WARN_ON_ONCE(!hooks || i >= hooks->num_hook_entries)) {
		kfree_skb(skb);
		kfree(entry);
		return;
	}

	hook_entry = &hooks->hooks[i];

	/* Continue traversal iff userspace said ok... */
	if (verdict == NF_REPEAT)
		verdict = nf_hook_entry_hookfn(hook_entry, skb, &entry->state);

	if (verdict == NF_ACCEPT) {
		if (nf_reroute(skb, entry) < 0)
			verdict = NF_DROP;
	}

	if (verdict == NF_ACCEPT) {
next_hook:
		++i;
		verdict = nf_iterate(skb, &entry->state, hooks, &i);
	}

	switch (verdict & NF_VERDICT_MASK) {
	case NF_ACCEPT:
	case NF_STOP:
		local_bh_disable();
		entry->state.okfn(entry->state.net, entry->state.sk, skb);
		local_bh_enable();
		break;
	case NF_QUEUE:
		err = nf_queue(skb, &entry->state, i, verdict);
		if (err == 1)
			goto next_hook;
		break;
	case NF_STOLEN:
		break;
	default:
		kfree_skb(skb);
	}

	kfree(entry);
}