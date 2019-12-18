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
struct TYPE_4__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct tipc_subscr {TYPE_2__ seq; } ;
struct TYPE_3__ {struct tipc_subscr s; } ;
struct tipc_subscription {int inactive; int /*<<< orphan*/  lock; TYPE_1__ evt; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_SUBSCR_TIMEOUT ; 
 struct tipc_subscription* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct tipc_subscription* sub ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tipc_sub_send_event (struct tipc_subscription*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_sub_timeout(struct timer_list *t)
{
	struct tipc_subscription *sub = from_timer(sub, t, timer);
	struct tipc_subscr *s = &sub->evt.s;

	spin_lock(&sub->lock);
	tipc_sub_send_event(sub, s->seq.lower, s->seq.upper,
			    TIPC_SUBSCR_TIMEOUT, 0, 0);
	sub->inactive = true;
	spin_unlock(&sub->lock);
}