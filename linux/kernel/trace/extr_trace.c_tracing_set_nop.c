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
struct trace_array {TYPE_1__* current_trace; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct trace_array*) ;int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 TYPE_1__ nop_trace ; 
 int /*<<< orphan*/  stub1 (struct trace_array*) ; 

__attribute__((used)) static void tracing_set_nop(struct trace_array *tr)
{
	if (tr->current_trace == &nop_trace)
		return;
	
	tr->current_trace->enabled--;

	if (tr->current_trace->reset)
		tr->current_trace->reset(tr);

	tr->current_trace = &nop_trace;
}