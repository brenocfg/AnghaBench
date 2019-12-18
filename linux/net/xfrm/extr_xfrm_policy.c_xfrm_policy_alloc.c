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
struct TYPE_4__ {int /*<<< orphan*/  hold_timer; int /*<<< orphan*/  hold_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  all; } ;
struct xfrm_policy {TYPE_2__ polq; int /*<<< orphan*/  timer; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  byidx; int /*<<< orphan*/  bydst; int /*<<< orphan*/  bydst_inexact_list; TYPE_1__ walk; int /*<<< orphan*/  xp_net; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct xfrm_policy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  xfrm_policy_queue_process ; 
 int /*<<< orphan*/  xfrm_policy_timer ; 

struct xfrm_policy *xfrm_policy_alloc(struct net *net, gfp_t gfp)
{
	struct xfrm_policy *policy;

	policy = kzalloc(sizeof(struct xfrm_policy), gfp);

	if (policy) {
		write_pnet(&policy->xp_net, net);
		INIT_LIST_HEAD(&policy->walk.all);
		INIT_HLIST_NODE(&policy->bydst_inexact_list);
		INIT_HLIST_NODE(&policy->bydst);
		INIT_HLIST_NODE(&policy->byidx);
		rwlock_init(&policy->lock);
		refcount_set(&policy->refcnt, 1);
		skb_queue_head_init(&policy->polq.hold_queue);
		timer_setup(&policy->timer, xfrm_policy_timer, 0);
		timer_setup(&policy->polq.hold_timer,
			    xfrm_policy_queue_process, 0);
	}
	return policy;
}