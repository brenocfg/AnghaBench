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
struct list_head {TYPE_1__* next; } ;
struct ip_vs_service {int /*<<< orphan*/  sched_lock; scalar_t__ sched_data; } ;
struct ip_vs_dest {struct list_head n_list; } ;
struct TYPE_2__ {scalar_t__ prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip_vs_rr_del_dest(struct ip_vs_service *svc, struct ip_vs_dest *dest)
{
	struct list_head *p;

	spin_lock_bh(&svc->sched_lock);
	p = (struct list_head *) svc->sched_data;
	/* dest is already unlinked, so p->prev is not valid but
	 * p->next is valid, use it to reach previous entry.
	 */
	if (p == &dest->n_list)
		svc->sched_data = p->next->prev;
	spin_unlock_bh(&svc->sched_lock);
	return 0;
}