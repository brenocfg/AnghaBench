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
typedef  int u32 ;
struct tcf_idrinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  action_idr; } ;
struct tc_action_net {struct tcf_idrinfo* idrinfo; } ;
struct tc_action {int /*<<< orphan*/  tcfa_bindcnt; int /*<<< orphan*/  tcfa_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tc_action*) ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int idr_alloc_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 struct tc_action* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

int tcf_idr_check_alloc(struct tc_action_net *tn, u32 *index,
			struct tc_action **a, int bind)
{
	struct tcf_idrinfo *idrinfo = tn->idrinfo;
	struct tc_action *p;
	int ret;

again:
	mutex_lock(&idrinfo->lock);
	if (*index) {
		p = idr_find(&idrinfo->action_idr, *index);
		if (IS_ERR(p)) {
			/* This means that another process allocated
			 * index but did not assign the pointer yet.
			 */
			mutex_unlock(&idrinfo->lock);
			goto again;
		}

		if (p) {
			refcount_inc(&p->tcfa_refcnt);
			if (bind)
				atomic_inc(&p->tcfa_bindcnt);
			*a = p;
			ret = 1;
		} else {
			*a = NULL;
			ret = idr_alloc_u32(&idrinfo->action_idr, NULL, index,
					    *index, GFP_KERNEL);
			if (!ret)
				idr_replace(&idrinfo->action_idr,
					    ERR_PTR(-EBUSY), *index);
		}
	} else {
		*index = 1;
		*a = NULL;
		ret = idr_alloc_u32(&idrinfo->action_idr, NULL, index,
				    UINT_MAX, GFP_KERNEL);
		if (!ret)
			idr_replace(&idrinfo->action_idr, ERR_PTR(-EBUSY),
				    *index);
	}
	mutex_unlock(&idrinfo->lock);
	return ret;
}