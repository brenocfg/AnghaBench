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
struct tc_action {int /*<<< orphan*/  tcfa_rate_est; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct tc_action*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_tcf (struct tc_action*) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tc_action*) ; 

__attribute__((used)) static void tcf_action_cleanup(struct tc_action *p)
{
	if (p->ops->cleanup)
		p->ops->cleanup(p);

	gen_kill_estimator(&p->tcfa_rate_est);
	free_tcf(p);
}