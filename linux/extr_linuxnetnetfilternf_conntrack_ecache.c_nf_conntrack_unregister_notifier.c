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
struct nf_ct_event_notifier {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nf_conntrack_event_cb; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_ecache_mutex ; 
 struct nf_ct_event_notifier* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nf_conntrack_unregister_notifier(struct net *net,
				      struct nf_ct_event_notifier *new)
{
	struct nf_ct_event_notifier *notify;

	mutex_lock(&nf_ct_ecache_mutex);
	notify = rcu_dereference_protected(net->ct.nf_conntrack_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	BUG_ON(notify != new);
	RCU_INIT_POINTER(net->ct.nf_conntrack_event_cb, NULL);
	mutex_unlock(&nf_ct_ecache_mutex);
	/* synchronize_rcu() is called from ctnetlink_exit. */
}