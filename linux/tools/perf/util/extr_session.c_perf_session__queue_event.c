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
typedef  int /*<<< orphan*/  u64 ;
struct perf_session {int /*<<< orphan*/  ordered_events; } ;

/* Variables and functions */
 int ordered_events__queue (int /*<<< orphan*/ *,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int perf_session__queue_event(struct perf_session *s, union perf_event *event,
			      u64 timestamp, u64 file_offset)
{
	return ordered_events__queue(&s->ordered_events, event, timestamp, file_offset);
}