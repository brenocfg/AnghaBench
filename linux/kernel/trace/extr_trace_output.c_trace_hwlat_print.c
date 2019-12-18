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
struct trace_seq {int dummy; } ;
struct trace_iterator {struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_event {int dummy; } ;
struct trace_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct hwlat_entry {scalar_t__ nmi_count; scalar_t__ nmi_total_ts; TYPE_1__ timestamp; int /*<<< orphan*/  outer_duration; int /*<<< orphan*/  duration; int /*<<< orphan*/  seqnum; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_GENERIC_SCHED_CLOCK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_assign_type (struct hwlat_entry*,struct trace_entry*) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

__attribute__((used)) static enum print_line_t
trace_hwlat_print(struct trace_iterator *iter, int flags,
		  struct trace_event *event)
{
	struct trace_entry *entry = iter->ent;
	struct trace_seq *s = &iter->seq;
	struct hwlat_entry *field;

	trace_assign_type(field, entry);

	trace_seq_printf(s, "#%-5u inner/outer(us): %4llu/%-5llu ts:%lld.%09ld",
			 field->seqnum,
			 field->duration,
			 field->outer_duration,
			 (long long)field->timestamp.tv_sec,
			 field->timestamp.tv_nsec);

	if (field->nmi_count) {
		/*
		 * The generic sched_clock() is not NMI safe, thus
		 * we only record the count and not the time.
		 */
		if (!IS_ENABLED(CONFIG_GENERIC_SCHED_CLOCK))
			trace_seq_printf(s, " nmi-total:%llu",
					 field->nmi_total_ts);
		trace_seq_printf(s, " nmi-count:%u",
				 field->nmi_count);
	}

	trace_seq_putc(s, '\n');

	return trace_handle_return(s);
}