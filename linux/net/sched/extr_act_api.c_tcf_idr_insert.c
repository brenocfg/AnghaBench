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
struct tc_action_net {struct tcf_idrinfo* idrinfo; } ;
struct tc_action {int /*<<< orphan*/  tcfa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct tc_action*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void tcf_idr_insert(struct tc_action_net *tn, struct tc_action *a)
{
	struct tcf_idrinfo *idrinfo = tn->idrinfo;

	mutex_lock(&idrinfo->lock);
	/* Replace ERR_PTR(-EBUSY) allocated by tcf_idr_check_alloc */
	WARN_ON(!IS_ERR(idr_replace(&idrinfo->action_idr, a, a->tcfa_index)));
	mutex_unlock(&idrinfo->lock);
}