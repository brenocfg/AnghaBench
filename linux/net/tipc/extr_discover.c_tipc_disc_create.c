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
struct tipc_net {scalar_t__ addr_trial_end; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_discoverer {int /*<<< orphan*/  skb; scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; scalar_t__ num_nodes; int /*<<< orphan*/  domain; int /*<<< orphan*/  bearer_id; struct net* net; int /*<<< orphan*/  dest; } ;
struct tipc_bearer {struct tipc_discoverer* disc; int /*<<< orphan*/  domain; int /*<<< orphan*/  identity; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_REQ_MSG ; 
 int /*<<< orphan*/  DSC_TRIAL_MSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_H_SIZE ; 
 scalar_t__ NODE_ID_LEN ; 
 scalar_t__ TIPC_DISC_INIT ; 
 int /*<<< orphan*/  buf_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct tipc_discoverer*) ; 
 struct tipc_discoverer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_media_addr*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msg_set_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_buf_acquire (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_disc_init_msg (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_bearer*) ; 
 int /*<<< orphan*/  tipc_disc_timeout ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

int tipc_disc_create(struct net *net, struct tipc_bearer *b,
		     struct tipc_media_addr *dest, struct sk_buff **skb)
{
	struct tipc_net *tn = tipc_net(net);
	struct tipc_discoverer *d;

	d = kmalloc(sizeof(*d), GFP_ATOMIC);
	if (!d)
		return -ENOMEM;
	d->skb = tipc_buf_acquire(MAX_H_SIZE + NODE_ID_LEN, GFP_ATOMIC);
	if (!d->skb) {
		kfree(d);
		return -ENOMEM;
	}
	tipc_disc_init_msg(net, d->skb, DSC_REQ_MSG, b);

	/* Do we need an address trial period first ? */
	if (!tipc_own_addr(net)) {
		tn->addr_trial_end = jiffies + msecs_to_jiffies(1000);
		msg_set_type(buf_msg(d->skb), DSC_TRIAL_MSG);
	}
	memcpy(&d->dest, dest, sizeof(*dest));
	d->net = net;
	d->bearer_id = b->identity;
	d->domain = b->domain;
	d->num_nodes = 0;
	d->timer_intv = TIPC_DISC_INIT;
	spin_lock_init(&d->lock);
	timer_setup(&d->timer, tipc_disc_timeout, 0);
	mod_timer(&d->timer, jiffies + d->timer_intv);
	b->disc = d;
	*skb = skb_clone(d->skb, GFP_ATOMIC);
	return 0;
}