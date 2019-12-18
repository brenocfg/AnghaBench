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
struct perf_event_header {int dummy; } ;
struct TYPE_4__ {int sample_type; } ;
struct perf_event {int read_size; int header_size; int id_header_size; TYPE_2__ attr; TYPE_1__* group_leader; } ;
struct TYPE_3__ {scalar_t__ nr_siblings; } ;

/* Variables and functions */
 int PERF_SAMPLE_READ ; 
 int /*<<< orphan*/  __perf_event_header_size (struct perf_event*,int) ; 
 int /*<<< orphan*/  __perf_event_read_size (struct perf_event*,scalar_t__) ; 
 int /*<<< orphan*/  perf_event__id_header_size (struct perf_event*) ; 

__attribute__((used)) static bool perf_event_validate_size(struct perf_event *event)
{
	/*
	 * The values computed here will be over-written when we actually
	 * attach the event.
	 */
	__perf_event_read_size(event, event->group_leader->nr_siblings + 1);
	__perf_event_header_size(event, event->attr.sample_type & ~PERF_SAMPLE_READ);
	perf_event__id_header_size(event);

	/*
	 * Sum the lot; should not exceed the 64k limit we have on records.
	 * Conservative limit to allow for callchains and other variable fields.
	 */
	if (event->read_size + event->header_size +
	    event->id_header_size + sizeof(struct perf_event_header) >= 16*1024)
		return false;

	return true;
}