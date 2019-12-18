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
struct hist_entry {scalar_t__ thread; TYPE_1__* callchain; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  (* hpp_field_fn ) (struct hist_entry*) ;
struct TYPE_6__ {scalar_t__ order; } ;
struct TYPE_5__ {int /*<<< orphan*/  use_callchain; scalar_t__ cumulate_callchain; } ;
struct TYPE_4__ {int max_depth; } ;

/* Variables and functions */
 scalar_t__ ORDER_CALLER ; 
 TYPE_3__ callchain_param ; 
 int field_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_entry__has_callchains (struct hist_entry*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static int __hpp__sort_acc(struct hist_entry *a, struct hist_entry *b,
			   hpp_field_fn get_field)
{
	s64 ret = 0;

	if (symbol_conf.cumulate_callchain) {
		/*
		 * Put caller above callee when they have equal period.
		 */
		ret = field_cmp(get_field(a), get_field(b));
		if (ret)
			return ret;

		if (a->thread != b->thread || !hist_entry__has_callchains(a) || !symbol_conf.use_callchain)
			return 0;

		ret = b->callchain->max_depth - a->callchain->max_depth;
		if (callchain_param.order == ORDER_CALLER)
			ret = -ret;
	}
	return ret;
}