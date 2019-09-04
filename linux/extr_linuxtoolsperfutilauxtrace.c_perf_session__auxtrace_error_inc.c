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
struct auxtrace_error_event {size_t type; } ;
union perf_event {struct auxtrace_error_event auxtrace_error; } ;
struct perf_session {TYPE_2__* evlist; } ;
struct TYPE_3__ {int* nr_auxtrace_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t PERF_AUXTRACE_ERROR_MAX ; 

void perf_session__auxtrace_error_inc(struct perf_session *session,
				      union perf_event *event)
{
	struct auxtrace_error_event *e = &event->auxtrace_error;

	if (e->type < PERF_AUXTRACE_ERROR_MAX)
		session->evlist->stats.nr_auxtrace_errors[e->type] += 1;
}