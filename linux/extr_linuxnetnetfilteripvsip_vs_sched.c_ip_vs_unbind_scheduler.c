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
struct ip_vs_service {int /*<<< orphan*/  scheduler; } ;
struct ip_vs_scheduler {int /*<<< orphan*/  (* done_service ) (struct ip_vs_service*) ;} ;

/* Variables and functions */
 struct ip_vs_scheduler* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_service*) ; 

void ip_vs_unbind_scheduler(struct ip_vs_service *svc,
			    struct ip_vs_scheduler *sched)
{
	struct ip_vs_scheduler *cur_sched;

	cur_sched = rcu_dereference_protected(svc->scheduler, 1);
	/* This check proves that old 'sched' was installed */
	if (!cur_sched)
		return;

	if (sched->done_service)
		sched->done_service(svc);
	/* svc->scheduler can be set to NULL only by caller */
}