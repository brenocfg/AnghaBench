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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_offset; } ;
struct perf_session {TYPE_1__ header; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __perf_session__process_events (struct perf_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __perf_session__process_pipe_events (struct perf_session*) ; 
 int /*<<< orphan*/  perf_data__is_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_data__size (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__register_idle_thread (struct perf_session*) ; 

int perf_session__process_events(struct perf_session *session)
{
	u64 size = perf_data__size(session->data);
	int err;

	if (perf_session__register_idle_thread(session) < 0)
		return -ENOMEM;

	if (!perf_data__is_pipe(session->data))
		err = __perf_session__process_events(session,
						     session->header.data_offset,
						     session->header.data_size, size);
	else
		err = __perf_session__process_pipe_events(session);

	return err;
}