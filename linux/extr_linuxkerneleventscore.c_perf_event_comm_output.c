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
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct perf_event {int dummy; } ;
struct TYPE_4__ {int size; } ;
struct TYPE_3__ {TYPE_2__ header; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct perf_comm_event {TYPE_1__ event_id; int /*<<< orphan*/  comm_size; int /*<<< orphan*/  comm; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  __output_copy (struct perf_output_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__output_id_sample (struct perf_event*,struct perf_output_handle*,struct perf_sample_data*) ; 
 int /*<<< orphan*/  perf_event_comm_match (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_header__init_id (TYPE_2__*,struct perf_sample_data*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_pid (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_tid (struct perf_event*,int /*<<< orphan*/ ) ; 
 int perf_output_begin (struct perf_output_handle*,struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_put (struct perf_output_handle*,TYPE_1__) ; 

__attribute__((used)) static void perf_event_comm_output(struct perf_event *event,
				   void *data)
{
	struct perf_comm_event *comm_event = data;
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	int size = comm_event->event_id.header.size;
	int ret;

	if (!perf_event_comm_match(event))
		return;

	perf_event_header__init_id(&comm_event->event_id.header, &sample, event);
	ret = perf_output_begin(&handle, event,
				comm_event->event_id.header.size);

	if (ret)
		goto out;

	comm_event->event_id.pid = perf_event_pid(event, comm_event->task);
	comm_event->event_id.tid = perf_event_tid(event, comm_event->task);

	perf_output_put(&handle, comm_event->event_id);
	__output_copy(&handle, comm_event->comm,
				   comm_event->comm_size);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	comm_event->event_id.header.size = size;
}