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
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {TYPE_2__ header; } ;
struct perf_bpf_event {TYPE_1__ event_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_event__output_id_sample (struct perf_event*,struct perf_output_handle*,struct perf_sample_data*) ; 
 int /*<<< orphan*/  perf_event_bpf_match (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_header__init_id (TYPE_2__*,struct perf_sample_data*,struct perf_event*) ; 
 int perf_output_begin (struct perf_output_handle*,struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_put (struct perf_output_handle*,TYPE_1__) ; 

__attribute__((used)) static void perf_event_bpf_output(struct perf_event *event, void *data)
{
	struct perf_bpf_event *bpf_event = data;
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	int ret;

	if (!perf_event_bpf_match(event))
		return;

	perf_event_header__init_id(&bpf_event->event_id.header,
				   &sample, event);
	ret = perf_output_begin(&handle, event,
				bpf_event->event_id.header.size);
	if (ret)
		return;

	perf_output_put(&handle, bpf_event->event_id);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
}