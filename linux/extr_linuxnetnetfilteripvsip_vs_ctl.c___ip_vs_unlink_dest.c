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
struct ip_vs_service {scalar_t__ af; int /*<<< orphan*/  scheduler; TYPE_1__* ipvs; int /*<<< orphan*/  num_dests; } ;
struct ip_vs_scheduler {int /*<<< orphan*/  (* del_dest ) (struct ip_vs_service*,struct ip_vs_dest*) ;} ;
struct ip_vs_dest {scalar_t__ af; int /*<<< orphan*/  n_list; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mixed_address_family_dests; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DEST_F_AVAILABLE ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct ip_vs_scheduler* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_service*,struct ip_vs_dest*) ; 

__attribute__((used)) static void __ip_vs_unlink_dest(struct ip_vs_service *svc,
				struct ip_vs_dest *dest,
				int svcupd)
{
	dest->flags &= ~IP_VS_DEST_F_AVAILABLE;

	/*
	 *  Remove it from the d-linked destination list.
	 */
	list_del_rcu(&dest->n_list);
	svc->num_dests--;

	if (dest->af != svc->af)
		svc->ipvs->mixed_address_family_dests--;

	if (svcupd) {
		struct ip_vs_scheduler *sched;

		sched = rcu_dereference_protected(svc->scheduler, 1);
		if (sched && sched->del_dest)
			sched->del_dest(svc, dest);
	}
}