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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_net {int /*<<< orphan*/  trial_addr; int /*<<< orphan*/  addr_trial_end; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_discoverer {int timer_intv; int /*<<< orphan*/  lock; int /*<<< orphan*/  bearer_id; int /*<<< orphan*/  skb; int /*<<< orphan*/  dest; int /*<<< orphan*/  timer; scalar_t__ num_nodes; int /*<<< orphan*/  domain; struct net* net; } ;
struct timer_list {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  maddr ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_REQ_MSG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TIPC_DISC_FAST ; 
 int TIPC_DISC_INACTIVE ; 
 int TIPC_DISC_INIT ; 
 int TIPC_DISC_SLOW ; 
 int /*<<< orphan*/  buf_msg (int /*<<< orphan*/ ) ; 
 struct tipc_discoverer* d ; 
 struct tipc_discoverer* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (struct tipc_media_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_set_prevnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tipc_bearer_xmit_skb (struct net*,int /*<<< orphan*/ ,struct sk_buff*,struct tipc_media_addr*) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 scalar_t__ tipc_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/  tipc_sched_net_finalize (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_disc_timeout(struct timer_list *t)
{
	struct tipc_discoverer *d = from_timer(d, t, timer);
	struct tipc_net *tn = tipc_net(d->net);
	struct tipc_media_addr maddr;
	struct sk_buff *skb = NULL;
	struct net *net = d->net;
	u32 bearer_id;

	spin_lock_bh(&d->lock);

	/* Stop searching if only desired node has been found */
	if (tipc_node(d->domain) && d->num_nodes) {
		d->timer_intv = TIPC_DISC_INACTIVE;
		goto exit;
	}

	/* Did we just leave trial period ? */
	if (!time_before(jiffies, tn->addr_trial_end) && !tipc_own_addr(net)) {
		mod_timer(&d->timer, jiffies + TIPC_DISC_INIT);
		spin_unlock_bh(&d->lock);
		tipc_sched_net_finalize(net, tn->trial_addr);
		return;
	}

	/* Adjust timeout interval according to discovery phase */
	if (time_before(jiffies, tn->addr_trial_end)) {
		d->timer_intv = TIPC_DISC_INIT;
	} else {
		d->timer_intv *= 2;
		if (d->num_nodes && d->timer_intv > TIPC_DISC_SLOW)
			d->timer_intv = TIPC_DISC_SLOW;
		else if (!d->num_nodes && d->timer_intv > TIPC_DISC_FAST)
			d->timer_intv = TIPC_DISC_FAST;
		msg_set_type(buf_msg(d->skb), DSC_REQ_MSG);
		msg_set_prevnode(buf_msg(d->skb), tn->trial_addr);
	}

	mod_timer(&d->timer, jiffies + d->timer_intv);
	memcpy(&maddr, &d->dest, sizeof(maddr));
	skb = skb_clone(d->skb, GFP_ATOMIC);
	bearer_id = d->bearer_id;
exit:
	spin_unlock_bh(&d->lock);
	if (skb)
		tipc_bearer_xmit_skb(net, bearer_id, skb, &maddr);
}