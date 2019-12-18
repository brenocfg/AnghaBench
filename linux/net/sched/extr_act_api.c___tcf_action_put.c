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
struct tcf_idrinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  action_idr; } ;
struct tc_action {int /*<<< orphan*/  tcfa_bindcnt; int /*<<< orphan*/  tcfa_index; int /*<<< orphan*/  tcfa_refcnt; struct tcf_idrinfo* idrinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_action_cleanup (struct tc_action*) ; 

__attribute__((used)) static int __tcf_action_put(struct tc_action *p, bool bind)
{
	struct tcf_idrinfo *idrinfo = p->idrinfo;

	if (refcount_dec_and_mutex_lock(&p->tcfa_refcnt, &idrinfo->lock)) {
		if (bind)
			atomic_dec(&p->tcfa_bindcnt);
		idr_remove(&idrinfo->action_idr, p->tcfa_index);
		mutex_unlock(&idrinfo->lock);

		tcf_action_cleanup(p);
		return 1;
	}

	if (bind)
		atomic_dec(&p->tcfa_bindcnt);

	return 0;
}