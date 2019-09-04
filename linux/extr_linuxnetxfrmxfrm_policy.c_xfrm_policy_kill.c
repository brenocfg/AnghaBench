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
struct TYPE_4__ {int /*<<< orphan*/  hold_queue; int /*<<< orphan*/  hold_timer; } ;
struct TYPE_3__ {int dead; } ;
struct xfrm_policy {int /*<<< orphan*/  timer; TYPE_2__ polq; int /*<<< orphan*/  genid; TYPE_1__ walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 

__attribute__((used)) static void xfrm_policy_kill(struct xfrm_policy *policy)
{
	policy->walk.dead = 1;

	atomic_inc(&policy->genid);

	if (del_timer(&policy->polq.hold_timer))
		xfrm_pol_put(policy);
	skb_queue_purge(&policy->polq.hold_queue);

	if (del_timer(&policy->timer))
		xfrm_pol_put(policy);

	xfrm_pol_put(policy);
}