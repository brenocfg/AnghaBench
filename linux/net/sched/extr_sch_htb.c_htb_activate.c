#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {int dummy; } ;
struct TYPE_6__ {TYPE_2__* q; } ;
struct htb_class {int prio_activity; int prio; TYPE_3__ leaf; scalar_t__ level; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_activate_prios (struct htb_sched*,struct htb_class*) ; 

__attribute__((used)) static inline void htb_activate(struct htb_sched *q, struct htb_class *cl)
{
	WARN_ON(cl->level || !cl->leaf.q || !cl->leaf.q->q.qlen);

	if (!cl->prio_activity) {
		cl->prio_activity = 1 << cl->prio;
		htb_activate_prios(q, cl);
	}
}