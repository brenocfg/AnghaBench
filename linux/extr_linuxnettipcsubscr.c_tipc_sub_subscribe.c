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
typedef  scalar_t__ u32 ;
struct tipc_subscr {int dummy; } ;
struct TYPE_3__ {struct tipc_subscr s; } ;
struct tipc_subscription {int conid; int inactive; int /*<<< orphan*/  timer; TYPE_1__ evt; int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; struct net* net; int /*<<< orphan*/  sub_list; int /*<<< orphan*/  service_list; } ;
struct net {int dummy; } ;
struct TYPE_4__ {scalar_t__ lower; scalar_t__ upper; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ TIPC_SUB_PORTS ; 
 scalar_t__ TIPC_SUB_SERVICE ; 
 scalar_t__ TIPC_WAIT_FOREVER ; 
 scalar_t__ filter ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct tipc_subscription*) ; 
 struct tipc_subscription* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct tipc_subscr*,struct tipc_subscr*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_2__ seq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nametbl_subscribe (struct tipc_subscription*) ; 
 scalar_t__ tipc_sub_read (struct tipc_subscr*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_sub_timeout ; 

struct tipc_subscription *tipc_sub_subscribe(struct net *net,
					     struct tipc_subscr *s,
					     int conid)
{
	u32 filter = tipc_sub_read(s, filter);
	struct tipc_subscription *sub;
	u32 timeout;

	if ((filter & TIPC_SUB_PORTS && filter & TIPC_SUB_SERVICE) ||
	    (tipc_sub_read(s, seq.lower) > tipc_sub_read(s, seq.upper))) {
		pr_warn("Subscription rejected, illegal request\n");
		return NULL;
	}
	sub = kmalloc(sizeof(*sub), GFP_ATOMIC);
	if (!sub) {
		pr_warn("Subscription rejected, no memory\n");
		return NULL;
	}
	INIT_LIST_HEAD(&sub->service_list);
	INIT_LIST_HEAD(&sub->sub_list);
	sub->net = net;
	sub->conid = conid;
	sub->inactive = false;
	memcpy(&sub->evt.s, s, sizeof(*s));
	spin_lock_init(&sub->lock);
	kref_init(&sub->kref);
	if (!tipc_nametbl_subscribe(sub)) {
		kfree(sub);
		return NULL;
	}
	timer_setup(&sub->timer, tipc_sub_timeout, 0);
	timeout = tipc_sub_read(&sub->evt.s, timeout);
	if (timeout != TIPC_WAIT_FOREVER)
		mod_timer(&sub->timer, jiffies + msecs_to_jiffies(timeout));
	return sub;
}