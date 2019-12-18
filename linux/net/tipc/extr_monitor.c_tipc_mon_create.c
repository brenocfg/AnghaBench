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
struct tipc_peer {int peer_cnt; int is_up; int is_head; scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; struct tipc_peer* domain; struct tipc_peer* self; struct net* net; int /*<<< orphan*/  lock; } ;
struct tipc_net {int random; struct tipc_peer** monitors; } ;
struct tipc_monitor {int peer_cnt; int is_up; int is_head; scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; struct tipc_monitor* domain; struct tipc_monitor* self; struct net* net; int /*<<< orphan*/  lock; } ;
struct tipc_mon_domain {int peer_cnt; int is_up; int is_head; scalar_t__ timer_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  list; int /*<<< orphan*/  addr; struct tipc_mon_domain* domain; struct tipc_mon_domain* self; struct net* net; int /*<<< orphan*/  lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MON_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct tipc_peer*) ; 
 struct tipc_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mon_timeout ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

int tipc_mon_create(struct net *net, int bearer_id)
{
	struct tipc_net *tn = tipc_net(net);
	struct tipc_monitor *mon;
	struct tipc_peer *self;
	struct tipc_mon_domain *dom;

	if (tn->monitors[bearer_id])
		return 0;

	mon = kzalloc(sizeof(*mon), GFP_ATOMIC);
	self = kzalloc(sizeof(*self), GFP_ATOMIC);
	dom = kzalloc(sizeof(*dom), GFP_ATOMIC);
	if (!mon || !self || !dom) {
		kfree(mon);
		kfree(self);
		kfree(dom);
		return -ENOMEM;
	}
	tn->monitors[bearer_id] = mon;
	rwlock_init(&mon->lock);
	mon->net = net;
	mon->peer_cnt = 1;
	mon->self = self;
	self->domain = dom;
	self->addr = tipc_own_addr(net);
	self->is_up = true;
	self->is_head = true;
	INIT_LIST_HEAD(&self->list);
	timer_setup(&mon->timer, mon_timeout, 0);
	mon->timer_intv = msecs_to_jiffies(MON_TIMEOUT + (tn->random & 0xffff));
	mod_timer(&mon->timer, jiffies + mon->timer_intv);
	return 0;
}