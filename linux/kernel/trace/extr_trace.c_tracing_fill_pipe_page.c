#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; } ;
struct TYPE_5__ {TYPE_1__ seq; } ;
struct trace_iterator {int /*<<< orphan*/ * ent; TYPE_2__ seq; } ;

/* Variables and functions */
 int TRACE_TYPE_NO_CONSUME ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int print_trace_line (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_consume (struct trace_iterator*) ; 
 int /*<<< orphan*/  trace_find_next_entry_inc (struct trace_iterator*) ; 
 scalar_t__ trace_seq_has_overflowed (TYPE_2__*) ; 
 int trace_seq_used (TYPE_2__*) ; 

__attribute__((used)) static size_t
tracing_fill_pipe_page(size_t rem, struct trace_iterator *iter)
{
	size_t count;
	int save_len;
	int ret;

	/* Seq buffer is page-sized, exactly what we need. */
	for (;;) {
		save_len = iter->seq.seq.len;
		ret = print_trace_line(iter);

		if (trace_seq_has_overflowed(&iter->seq)) {
			iter->seq.seq.len = save_len;
			break;
		}

		/*
		 * This should not be hit, because it should only
		 * be set if the iter->seq overflowed. But check it
		 * anyway to be safe.
		 */
		if (ret == TRACE_TYPE_PARTIAL_LINE) {
			iter->seq.seq.len = save_len;
			break;
		}

		count = trace_seq_used(&iter->seq) - save_len;
		if (rem < count) {
			rem = 0;
			iter->seq.seq.len = save_len;
			break;
		}

		if (ret != TRACE_TYPE_NO_CONSUME)
			trace_consume(iter);
		rem -= count;
		if (!trace_find_next_entry_inc(iter))	{
			rem = 0;
			iter->ent = NULL;
			break;
		}
	}

	return rem;
}