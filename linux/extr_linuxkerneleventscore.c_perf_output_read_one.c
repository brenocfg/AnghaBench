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
typedef  int u64 ;
struct perf_output_handle {int dummy; } ;
struct TYPE_2__ {int read_format; } ;
struct perf_event {int /*<<< orphan*/  child_total_time_running; int /*<<< orphan*/  child_total_time_enabled; TYPE_1__ attr; } ;

/* Variables and functions */
 int PERF_FORMAT_ID ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/  __output_copy (struct perf_output_handle*,int*,int) ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int perf_event_count (struct perf_event*) ; 
 int primary_event_id (struct perf_event*) ; 

__attribute__((used)) static void perf_output_read_one(struct perf_output_handle *handle,
				 struct perf_event *event,
				 u64 enabled, u64 running)
{
	u64 read_format = event->attr.read_format;
	u64 values[4];
	int n = 0;

	values[n++] = perf_event_count(event);
	if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED) {
		values[n++] = enabled +
			atomic64_read(&event->child_total_time_enabled);
	}
	if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING) {
		values[n++] = running +
			atomic64_read(&event->child_total_time_running);
	}
	if (read_format & PERF_FORMAT_ID)
		values[n++] = primary_event_id(event);

	__output_copy(handle, values, n * sizeof(u64));
}