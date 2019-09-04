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
struct tipc_media_addr {int dummy; } ;
struct tipc_discoverer {int /*<<< orphan*/  lock; int /*<<< orphan*/  skb; scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  dest; scalar_t__ num_nodes; int /*<<< orphan*/  domain; int /*<<< orphan*/  bearer_id; struct net* net; } ;
struct tipc_bearer {int /*<<< orphan*/  identity; int /*<<< orphan*/  domain; struct tipc_discoverer* disc; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  maddr ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_REQ_MSG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TIPC_DISC_INIT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (struct tipc_media_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* skb_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bearer_xmit_skb (struct net*,int /*<<< orphan*/ ,struct sk_buff*,struct tipc_media_addr*) ; 
 int /*<<< orphan*/  tipc_disc_init_msg (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_bearer*) ; 

void tipc_disc_reset(struct net *net, struct tipc_bearer *b)
{
	struct tipc_discoverer *d = b->disc;
	struct tipc_media_addr maddr;
	struct sk_buff *skb;

	spin_lock_bh(&d->lock);
	tipc_disc_init_msg(net, d->skb, DSC_REQ_MSG, b);
	d->net = net;
	d->bearer_id = b->identity;
	d->domain = b->domain;
	d->num_nodes = 0;
	d->timer_intv = TIPC_DISC_INIT;
	memcpy(&maddr, &d->dest, sizeof(maddr));
	mod_timer(&d->timer, jiffies + d->timer_intv);
	skb = skb_clone(d->skb, GFP_ATOMIC);
	spin_unlock_bh(&d->lock);
	if (skb)
		tipc_bearer_xmit_skb(net, b->identity, skb, &maddr);
}