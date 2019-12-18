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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_idrinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  action_idr; } ;
struct tc_action_net {struct tcf_idrinfo* idrinfo; } ;
struct tc_action {int /*<<< orphan*/  tcfa_refcnt; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tc_action*) ; 
 struct tc_action* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

int tcf_idr_search(struct tc_action_net *tn, struct tc_action **a, u32 index)
{
	struct tcf_idrinfo *idrinfo = tn->idrinfo;
	struct tc_action *p;

	mutex_lock(&idrinfo->lock);
	p = idr_find(&idrinfo->action_idr, index);
	if (IS_ERR(p))
		p = NULL;
	else if (p)
		refcount_inc(&p->tcfa_refcnt);
	mutex_unlock(&idrinfo->lock);

	if (p) {
		*a = p;
		return true;
	}
	return false;
}