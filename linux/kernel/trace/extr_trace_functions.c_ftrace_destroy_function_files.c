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
struct trace_array {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_destroy_filter_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void ftrace_destroy_function_files(struct trace_array *tr)
{
	ftrace_destroy_filter_files(tr->ops);
	kfree(tr->ops);
	tr->ops = NULL;
}