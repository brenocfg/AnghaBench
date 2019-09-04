#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct trace_array {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct hist_trigger_data {TYPE_2__* attrs; TYPE_1__* event_file; } ;
struct hist_field {struct hist_trigger_data* hist_data; } ;
struct TYPE_4__ {scalar_t__ ts_in_usecs; } ;
struct TYPE_3__ {struct trace_array* tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ns2usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_buffer_event_time_stamp (struct ring_buffer_event*) ; 
 scalar_t__ trace_clock_in_ns (struct trace_array*) ; 

__attribute__((used)) static u64 hist_field_timestamp(struct hist_field *hist_field,
				struct tracing_map_elt *elt,
				struct ring_buffer_event *rbe,
				void *event)
{
	struct hist_trigger_data *hist_data = hist_field->hist_data;
	struct trace_array *tr = hist_data->event_file->tr;

	u64 ts = ring_buffer_event_time_stamp(rbe);

	if (hist_data->attrs->ts_in_usecs && trace_clock_in_ns(tr))
		ts = ns2usecs(ts);

	return ts;
}