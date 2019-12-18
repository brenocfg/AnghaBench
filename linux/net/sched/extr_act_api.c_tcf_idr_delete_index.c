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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_idrinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  action_idr; } ;
struct tc_action {int /*<<< orphan*/  tcfa_index; TYPE_1__* ops; int /*<<< orphan*/  tcfa_refcnt; int /*<<< orphan*/  tcfa_bindcnt; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct module* owner; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct tc_action* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tc_action* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_action_cleanup (struct tc_action*) ; 

__attribute__((used)) static int tcf_idr_delete_index(struct tcf_idrinfo *idrinfo, u32 index)
{
	struct tc_action *p;
	int ret = 0;

	mutex_lock(&idrinfo->lock);
	p = idr_find(&idrinfo->action_idr, index);
	if (!p) {
		mutex_unlock(&idrinfo->lock);
		return -ENOENT;
	}

	if (!atomic_read(&p->tcfa_bindcnt)) {
		if (refcount_dec_and_test(&p->tcfa_refcnt)) {
			struct module *owner = p->ops->owner;

			WARN_ON(p != idr_remove(&idrinfo->action_idr,
						p->tcfa_index));
			mutex_unlock(&idrinfo->lock);

			tcf_action_cleanup(p);
			module_put(owner);
			return 0;
		}
		ret = 0;
	} else {
		ret = -EPERM;
	}

	mutex_unlock(&idrinfo->lock);
	return ret;
}