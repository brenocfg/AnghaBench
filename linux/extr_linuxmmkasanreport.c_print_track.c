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
struct stack_trace {int dummy; } ;
struct kasan_track {scalar_t__ stack; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  depot_fetch_stack (scalar_t__,struct stack_trace*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_stack_trace (struct stack_trace*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_track(struct kasan_track *track, const char *prefix)
{
	pr_err("%s by task %u:\n", prefix, track->pid);
	if (track->stack) {
		struct stack_trace trace;

		depot_fetch_stack(track->stack, &trace);
		print_stack_trace(&trace, 0);
	} else {
		pr_err("(stack is not available)\n");
	}
}