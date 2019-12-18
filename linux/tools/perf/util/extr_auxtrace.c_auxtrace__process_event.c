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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_tool {int dummy; } ;
struct perf_session {TYPE_1__* auxtrace; } ;
struct perf_sample {int dummy; } ;
struct TYPE_2__ {int (* process_event ) (struct perf_session*,union perf_event*,struct perf_sample*,struct perf_tool*) ;} ;

/* Variables and functions */
 int stub1 (struct perf_session*,union perf_event*,struct perf_sample*,struct perf_tool*) ; 

int auxtrace__process_event(struct perf_session *session, union perf_event *event,
			    struct perf_sample *sample, struct perf_tool *tool)
{
	if (!session->auxtrace)
		return 0;

	return session->auxtrace->process_event(session, event, sample, tool);
}