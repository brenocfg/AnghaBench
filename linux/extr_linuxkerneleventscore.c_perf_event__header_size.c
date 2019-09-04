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
struct TYPE_4__ {int /*<<< orphan*/  sample_type; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__* group_leader; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_siblings; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_header_size (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __perf_event_read_size (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_event__header_size(struct perf_event *event)
{
	__perf_event_read_size(event,
			       event->group_leader->nr_siblings);
	__perf_event_header_size(event, event->attr.sample_type);
}