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
struct perf_tool {int dummy; } ;
struct perf_session {TYPE_1__* auxtrace; } ;
struct TYPE_2__ {int (* flush_events ) (struct perf_session*,struct perf_tool*) ;} ;

/* Variables and functions */
 int stub1 (struct perf_session*,struct perf_tool*) ; 

int auxtrace__flush_events(struct perf_session *session, struct perf_tool *tool)
{
	if (!session->auxtrace)
		return 0;

	return session->auxtrace->flush_events(session, tool);
}