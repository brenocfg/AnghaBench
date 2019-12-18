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
struct TYPE_2__ {scalar_t__ feat_id; } ;
union perf_event {TYPE_1__ feat; } ;
struct perf_session {int dummy; } ;

/* Variables and functions */
 scalar_t__ HEADER_LAST_FEATURE ; 
 int perf_event__process_feature (struct perf_session*,union perf_event*) ; 

__attribute__((used)) static int process_feature_event(struct perf_session *session,
				 union perf_event *event)
{
	if (event->feat.feat_id < HEADER_LAST_FEATURE)
		return perf_event__process_feature(session, event);
	return 0;
}