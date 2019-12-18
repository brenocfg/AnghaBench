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
typedef  int /*<<< orphan*/  u16 ;
struct trace_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int preempt_count () ; 
 int /*<<< orphan*/  tracing_generic_entry_update (struct trace_entry*,int /*<<< orphan*/ ,unsigned long,int) ; 

void perf_trace_buf_update(void *record, u16 type)
{
	struct trace_entry *entry = record;
	int pc = preempt_count();
	unsigned long flags;

	local_save_flags(flags);
	tracing_generic_entry_update(entry, type, flags, pc);
}