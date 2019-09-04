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
struct trace_seq {int dummy; } ;
struct tep_record {unsigned long ts; } ;
struct tep_handle {int flags; scalar_t__ latency_format; int /*<<< orphan*/  trace_clock; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 unsigned long NSEC_PER_SEC ; 
 unsigned long NSEC_PER_USEC ; 
 int TEP_NSEC_OUTPUT ; 
 unsigned long USEC_PER_SEC ; 
 int is_timestamp_in_us (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tep_data_lat_fmt (struct tep_handle*,struct trace_seq*,struct tep_record*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long,...) ; 

void tep_print_event_time(struct tep_handle *pevent, struct trace_seq *s,
			  struct event_format *event,
			  struct tep_record *record,
			  bool use_trace_clock)
{
	unsigned long secs;
	unsigned long usecs;
	unsigned long nsecs;
	int p;
	bool use_usec_format;

	use_usec_format = is_timestamp_in_us(pevent->trace_clock,
							use_trace_clock);
	if (use_usec_format) {
		secs = record->ts / NSEC_PER_SEC;
		nsecs = record->ts - secs * NSEC_PER_SEC;
	}

	if (pevent->latency_format) {
		tep_data_lat_fmt(pevent, s, record);
	}

	if (use_usec_format) {
		if (pevent->flags & TEP_NSEC_OUTPUT) {
			usecs = nsecs;
			p = 9;
		} else {
			usecs = (nsecs + 500) / NSEC_PER_USEC;
			/* To avoid usecs larger than 1 sec */
			if (usecs >= USEC_PER_SEC) {
				usecs -= USEC_PER_SEC;
				secs++;
			}
			p = 6;
		}

		trace_seq_printf(s, " %5lu.%0*lu:", secs, p, usecs);
	} else
		trace_seq_printf(s, " %12llu:", record->ts);
}