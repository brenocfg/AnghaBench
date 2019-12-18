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
struct TYPE_2__ {unsigned int idx; int /*<<< orphan*/  size; int /*<<< orphan*/  reference; int /*<<< orphan*/  offset; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; } ;
union perf_event {TYPE_1__ auxtrace; } ;
struct perf_session {int dummy; } ;
struct auxtrace_queues {int dummy; } ;
struct auxtrace_buffer {int pid; int /*<<< orphan*/  size; int /*<<< orphan*/  reference; int /*<<< orphan*/  offset; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int auxtrace_queues__add_buffer (struct auxtrace_queues*,struct perf_session*,unsigned int,struct auxtrace_buffer*,struct auxtrace_buffer**) ; 

int auxtrace_queues__add_event(struct auxtrace_queues *queues,
			       struct perf_session *session,
			       union perf_event *event, off_t data_offset,
			       struct auxtrace_buffer **buffer_ptr)
{
	struct auxtrace_buffer buffer = {
		.pid = -1,
		.tid = event->auxtrace.tid,
		.cpu = event->auxtrace.cpu,
		.data_offset = data_offset,
		.offset = event->auxtrace.offset,
		.reference = event->auxtrace.reference,
		.size = event->auxtrace.size,
	};
	unsigned int idx = event->auxtrace.idx;

	return auxtrace_queues__add_buffer(queues, session, idx, &buffer,
					   buffer_ptr);
}