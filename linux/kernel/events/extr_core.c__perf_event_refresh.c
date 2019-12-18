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
struct TYPE_2__ {scalar_t__ inherit; } ;
struct perf_event {int /*<<< orphan*/  event_limit; TYPE_1__ attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _perf_event_enable (struct perf_event*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_sampling_event (struct perf_event*) ; 

__attribute__((used)) static int _perf_event_refresh(struct perf_event *event, int refresh)
{
	/*
	 * not supported on inherited events
	 */
	if (event->attr.inherit || !is_sampling_event(event))
		return -EINVAL;

	atomic_add(refresh, &event->event_limit);
	_perf_event_enable(event);

	return 0;
}