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
struct perf_event_attr {int type; } ;
struct TYPE_2__ {int type; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  PERF_TYPE_BREAKPOINT 128 
 int perf_event_modify_breakpoint (struct perf_event*,struct perf_event_attr*) ; 

__attribute__((used)) static int perf_event_modify_attr(struct perf_event *event,
				  struct perf_event_attr *attr)
{
	if (event->attr.type != attr->type)
		return -EINVAL;

	switch (event->attr.type) {
	case PERF_TYPE_BREAKPOINT:
		return perf_event_modify_breakpoint(event, attr);
	default:
		/* Place holder for future additions. */
		return -EOPNOTSUPP;
	}
}