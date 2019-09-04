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
struct TYPE_4__ {int /*<<< orphan*/  hold_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  dead; } ;
struct xfrm_policy {int /*<<< orphan*/  rcu; TYPE_2__ polq; int /*<<< orphan*/  timer; TYPE_1__ walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_policy_destroy_rcu ; 

void xfrm_policy_destroy(struct xfrm_policy *policy)
{
	BUG_ON(!policy->walk.dead);

	if (del_timer(&policy->timer) || del_timer(&policy->polq.hold_timer))
		BUG();

	call_rcu(&policy->rcu, xfrm_policy_destroy_rcu);
}