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
struct tracer {struct tracer* next; } ;
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_tracer_options (struct trace_array*,struct tracer*) ; 
 struct tracer* trace_types ; 

__attribute__((used)) static void __update_tracer_options(struct trace_array *tr)
{
	struct tracer *t;

	for (t = trace_types; t; t = t->next)
		add_tracer_options(tr, t);
}