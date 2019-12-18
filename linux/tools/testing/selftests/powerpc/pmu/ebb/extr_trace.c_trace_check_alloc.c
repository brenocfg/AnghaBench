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
struct trace_buffer {int overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_check_bounds (struct trace_buffer*,void*) ; 

__attribute__((used)) static bool trace_check_alloc(struct trace_buffer *tb, void *p)
{
	/*
	 * If we ever overflowed don't allow any more input. This prevents us
	 * from dropping a large item and then later logging a small one. The
	 * buffer should just stop when overflow happened, not be patchy. If
	 * you're overflowing, make your buffer bigger.
	 */
	if (tb->overflow)
		return false;

	if (!trace_check_bounds(tb, p)) {
		tb->overflow = true;
		return false;
	}

	return true;
}