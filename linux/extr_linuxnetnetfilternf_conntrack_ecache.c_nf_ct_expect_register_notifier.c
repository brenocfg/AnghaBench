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
struct nf_exp_event_notifier {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nf_expect_event_cb; } ;
struct net {TYPE_1__ ct; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_ecache_mutex ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_exp_event_notifier*) ; 
 struct nf_exp_event_notifier* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nf_ct_expect_register_notifier(struct net *net,
				   struct nf_exp_event_notifier *new)
{
	int ret;
	struct nf_exp_event_notifier *notify;

	mutex_lock(&nf_ct_ecache_mutex);
	notify = rcu_dereference_protected(net->ct.nf_expect_event_cb,
					   lockdep_is_held(&nf_ct_ecache_mutex));
	if (notify != NULL) {
		ret = -EBUSY;
		goto out_unlock;
	}
	rcu_assign_pointer(net->ct.nf_expect_event_cb, new);
	ret = 0;

out_unlock:
	mutex_unlock(&nf_ct_ecache_mutex);
	return ret;
}