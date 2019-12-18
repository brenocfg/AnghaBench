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
struct prog_entry {int when_to_branch; int target; struct filter_pred* pred; } ;
struct filter_pred {int (* fn ) (struct filter_pred*,void*) ;} ;
struct event_filter {int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 struct prog_entry* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int stub1 (struct filter_pred*,void*) ; 

int filter_match_preds(struct event_filter *filter, void *rec)
{
	struct prog_entry *prog;
	int i;

	/* no filter is considered a match */
	if (!filter)
		return 1;

	/* Protected by either SRCU(tracepoint_srcu) or preempt_disable */
	prog = rcu_dereference_raw(filter->prog);
	if (!prog)
		return 1;

	for (i = 0; prog[i].pred; i++) {
		struct filter_pred *pred = prog[i].pred;
		int match = pred->fn(pred, rec);
		if (match == prog[i].when_to_branch)
			i = prog[i].target;
	}
	return prog[i].target;
}