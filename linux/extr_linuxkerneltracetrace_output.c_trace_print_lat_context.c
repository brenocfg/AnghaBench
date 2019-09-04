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
typedef  int /*<<< orphan*/  u64 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {int ent_size; int /*<<< orphan*/  cpu; int /*<<< orphan*/  idx; int /*<<< orphan*/  ts; struct trace_entry* ent; struct trace_seq seq; struct trace_array* tr; } ;
struct trace_entry {int /*<<< orphan*/  preempt_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  pid; } ;
struct trace_array {unsigned long trace_flags; } ;

/* Variables and functions */
 int TASK_COMM_LEN ; 
 unsigned long TRACE_ITER_VERBOSE ; 
 int /*<<< orphan*/  lat_print_generic (struct trace_seq*,struct trace_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lat_print_timestamp (struct trace_iterator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_find_cmdline (int /*<<< orphan*/ ,char*) ; 
 struct trace_entry* trace_find_next_entry (struct trace_iterator*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_seq_has_overflowed (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int trace_print_lat_context(struct trace_iterator *iter)
{
	struct trace_array *tr = iter->tr;
	/* trace_find_next_entry will reset ent_size */
	int ent_size = iter->ent_size;
	struct trace_seq *s = &iter->seq;
	u64 next_ts;
	struct trace_entry *entry = iter->ent,
			   *next_entry = trace_find_next_entry(iter, NULL,
							       &next_ts);
	unsigned long verbose = (tr->trace_flags & TRACE_ITER_VERBOSE);

	/* Restore the original ent_size */
	iter->ent_size = ent_size;

	if (!next_entry)
		next_ts = iter->ts;

	if (verbose) {
		char comm[TASK_COMM_LEN];

		trace_find_cmdline(entry->pid, comm);

		trace_seq_printf(
			s, "%16s %5d %3d %d %08x %08lx ",
			comm, entry->pid, iter->cpu, entry->flags,
			entry->preempt_count, iter->idx);
	} else {
		lat_print_generic(s, entry, iter->cpu);
	}

	lat_print_timestamp(iter, next_ts);

	return !trace_seq_has_overflowed(s);
}