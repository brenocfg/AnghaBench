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
struct tracer {int dummy; } ;
struct trace_array {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_trace_option_files (struct trace_array*,struct tracer*) ; 

__attribute__((used)) static void add_tracer_options(struct trace_array *tr, struct tracer *t)
{
	/* Only enable if the directory has been created already. */
	if (!tr->dir)
		return;

	create_trace_option_files(tr, t);
}