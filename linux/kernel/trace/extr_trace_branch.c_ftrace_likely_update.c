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
struct TYPE_2__ {int /*<<< orphan*/  incorrect; int /*<<< orphan*/  correct; } ;
struct ftrace_likely_data {TYPE_1__ data; int /*<<< orphan*/  constant; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_likely_condition (struct ftrace_likely_data*,int,int) ; 
 int /*<<< orphan*/  user_access_restore (unsigned long) ; 
 unsigned long user_access_save () ; 

void ftrace_likely_update(struct ftrace_likely_data *f, int val,
			  int expect, int is_constant)
{
	unsigned long flags = user_access_save();

	/* A constant is always correct */
	if (is_constant) {
		f->constant++;
		val = expect;
	}
	/*
	 * I would love to have a trace point here instead, but the
	 * trace point code is so inundated with unlikely and likely
	 * conditions that the recursive nightmare that exists is too
	 * much to try to get working. At least for now.
	 */
	trace_likely_condition(f, val, expect);

	/* FIXME: Make this atomic! */
	if (val == expect)
		f->data.correct++;
	else
		f->data.incorrect++;

	user_access_restore(flags);
}