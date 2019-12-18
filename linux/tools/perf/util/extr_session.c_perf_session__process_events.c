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
struct perf_session {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __perf_session__process_events (struct perf_session*) ; 
 int __perf_session__process_pipe_events (struct perf_session*) ; 
 scalar_t__ perf_data__is_pipe (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_session__register_idle_thread (struct perf_session*) ; 

int perf_session__process_events(struct perf_session *session)
{
	if (perf_session__register_idle_thread(session) < 0)
		return -ENOMEM;

	if (perf_data__is_pipe(session->data))
		return __perf_session__process_pipe_events(session);

	return __perf_session__process_events(session);
}