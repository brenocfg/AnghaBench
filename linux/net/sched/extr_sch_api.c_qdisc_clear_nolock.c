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
struct Qdisc {int flags; int /*<<< orphan*/ * cpu_qstats; int /*<<< orphan*/ * cpu_bstats; } ;

/* Variables and functions */
 int TCQ_F_CPUSTATS ; 
 int TCQ_F_NOLOCK ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qdisc_clear_nolock(struct Qdisc *sch)
{
	sch->flags &= ~TCQ_F_NOLOCK;
	if (!(sch->flags & TCQ_F_CPUSTATS))
		return;

	free_percpu(sch->cpu_bstats);
	free_percpu(sch->cpu_qstats);
	sch->cpu_bstats = NULL;
	sch->cpu_qstats = NULL;
	sch->flags &= ~TCQ_F_CPUSTATS;
}