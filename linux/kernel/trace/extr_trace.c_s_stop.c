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
struct trace_iterator {int /*<<< orphan*/  cpu_file; scalar_t__ snapshot; TYPE_1__* trace; } ;
struct seq_file {struct trace_iterator* private; } ;
struct TYPE_2__ {scalar_t__ use_max_tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_access_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_event_read_unlock () ; 
 int /*<<< orphan*/  trace_record_taskinfo_disabled ; 

__attribute__((used)) static void s_stop(struct seq_file *m, void *p)
{
	struct trace_iterator *iter = m->private;

#ifdef CONFIG_TRACER_MAX_TRACE
	if (iter->snapshot && iter->trace->use_max_tr)
		return;
#endif

	if (!iter->snapshot)
		atomic_dec(&trace_record_taskinfo_disabled);

	trace_access_unlock(iter->cpu_file);
	trace_event_read_unlock();
}