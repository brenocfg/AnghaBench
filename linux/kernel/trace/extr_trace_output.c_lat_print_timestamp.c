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
typedef  unsigned long long u64 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {unsigned long iter_flags; unsigned long long ts; struct trace_seq seq; TYPE_1__* trace_buffer; struct trace_array* tr; } ;
struct trace_array {unsigned long trace_flags; } ;
struct TYPE_2__ {unsigned long long time_start; } ;

/* Variables and functions */
 unsigned long long NSEC_PER_USEC ; 
 unsigned long TRACE_FILE_TIME_IN_NS ; 
 unsigned long TRACE_ITER_VERBOSE ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 unsigned long do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long long ns2usecs (unsigned long long) ; 
 int /*<<< orphan*/  trace_find_mark (unsigned long long) ; 
 int /*<<< orphan*/  trace_seq_has_overflowed (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long long,...) ; 

__attribute__((used)) static int
lat_print_timestamp(struct trace_iterator *iter, u64 next_ts)
{
	struct trace_array *tr = iter->tr;
	unsigned long verbose = tr->trace_flags & TRACE_ITER_VERBOSE;
	unsigned long in_ns = iter->iter_flags & TRACE_FILE_TIME_IN_NS;
	unsigned long long abs_ts = iter->ts - iter->trace_buffer->time_start;
	unsigned long long rel_ts = next_ts - iter->ts;
	struct trace_seq *s = &iter->seq;

	if (in_ns) {
		abs_ts = ns2usecs(abs_ts);
		rel_ts = ns2usecs(rel_ts);
	}

	if (verbose && in_ns) {
		unsigned long abs_usec = do_div(abs_ts, USEC_PER_MSEC);
		unsigned long abs_msec = (unsigned long)abs_ts;
		unsigned long rel_usec = do_div(rel_ts, USEC_PER_MSEC);
		unsigned long rel_msec = (unsigned long)rel_ts;

		trace_seq_printf(
			s, "[%08llx] %ld.%03ldms (+%ld.%03ldms): ",
			ns2usecs(iter->ts),
			abs_msec, abs_usec,
			rel_msec, rel_usec);

	} else if (verbose && !in_ns) {
		trace_seq_printf(
			s, "[%016llx] %lld (+%lld): ",
			iter->ts, abs_ts, rel_ts);

	} else if (!verbose && in_ns) {
		trace_seq_printf(
			s, " %4lldus%c: ",
			abs_ts,
			trace_find_mark(rel_ts * NSEC_PER_USEC));

	} else { /* !verbose && !in_ns */
		trace_seq_printf(s, " %4lld: ", abs_ts);
	}

	return !trace_seq_has_overflowed(s);
}