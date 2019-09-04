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
struct htb_sched {int dummy; } ;
struct htb_class {scalar_t__ prio_activity; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_deactivate_prios (struct htb_sched*,struct htb_class*) ; 

__attribute__((used)) static inline void htb_deactivate(struct htb_sched *q, struct htb_class *cl)
{
	WARN_ON(!cl->prio_activity);

	htb_deactivate_prios(q, cl);
	cl->prio_activity = 0;
}