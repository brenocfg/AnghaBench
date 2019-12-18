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
typedef  union perf_event {int dummy; } perf_event ;
typedef  unsigned long long u64 ;
struct ordered_events {unsigned long long last_flush; int /*<<< orphan*/  nr_unordered_events; int /*<<< orphan*/  last_flush_type; } ;
struct ordered_event {unsigned long long file_offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIME ; 
 int /*<<< orphan*/  OE_FLUSH__HALF ; 
 int /*<<< orphan*/  ordered_events__flush (struct ordered_events*,int /*<<< orphan*/ ) ; 
 struct ordered_event* ordered_events__new_event (struct ordered_events*,unsigned long long,union perf_event*) ; 
 int /*<<< orphan*/  pr_oe_time (unsigned long long,char*,...) ; 

int ordered_events__queue(struct ordered_events *oe, union perf_event *event,
			  u64 timestamp, u64 file_offset)
{
	struct ordered_event *oevent;

	if (!timestamp || timestamp == ~0ULL)
		return -ETIME;

	if (timestamp < oe->last_flush) {
		pr_oe_time(timestamp,      "out of order event\n");
		pr_oe_time(oe->last_flush, "last flush, last_flush_type %d\n",
			   oe->last_flush_type);

		oe->nr_unordered_events++;
	}

	oevent = ordered_events__new_event(oe, timestamp, event);
	if (!oevent) {
		ordered_events__flush(oe, OE_FLUSH__HALF);
		oevent = ordered_events__new_event(oe, timestamp, event);
	}

	if (!oevent)
		return -ENOMEM;

	oevent->file_offset = file_offset;
	return 0;
}