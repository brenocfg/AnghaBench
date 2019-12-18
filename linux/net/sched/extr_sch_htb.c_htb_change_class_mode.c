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
struct htb_sched {int /*<<< orphan*/  overlimits; } ;
struct htb_class {int cmode; scalar_t__ prio_activity; int /*<<< orphan*/  overlimits; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum htb_cmode { ____Placeholder_htb_cmode } htb_cmode ;

/* Variables and functions */
 int HTB_CANT_SEND ; 
 int /*<<< orphan*/  htb_activate_prios (struct htb_sched*,struct htb_class*) ; 
 int htb_class_mode (struct htb_class*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htb_deactivate_prios (struct htb_sched*,struct htb_class*) ; 

__attribute__((used)) static void
htb_change_class_mode(struct htb_sched *q, struct htb_class *cl, s64 *diff)
{
	enum htb_cmode new_mode = htb_class_mode(cl, diff);

	if (new_mode == cl->cmode)
		return;

	if (new_mode == HTB_CANT_SEND) {
		cl->overlimits++;
		q->overlimits++;
	}

	if (cl->prio_activity) {	/* not necessary: speed optimization */
		if (cl->cmode != HTB_CANT_SEND)
			htb_deactivate_prios(q, cl);
		cl->cmode = new_mode;
		if (new_mode != HTB_CANT_SEND)
			htb_activate_prios(q, cl);
	} else
		cl->cmode = new_mode;
}