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
struct kasan_track {scalar_t__ stack; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 
 unsigned int stack_depot_fetch (scalar_t__,unsigned long**) ; 
 int /*<<< orphan*/  stack_trace_print (unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_track(struct kasan_track *track, const char *prefix)
{
	pr_err("%s by task %u:\n", prefix, track->pid);
	if (track->stack) {
		unsigned long *entries;
		unsigned int nr_entries;

		nr_entries = stack_depot_fetch(track->stack, &entries);
		stack_trace_print(entries, nr_entries, 0);
	} else {
		pr_err("(stack is not available)\n");
	}
}