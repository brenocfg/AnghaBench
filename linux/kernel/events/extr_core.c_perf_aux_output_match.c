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
struct perf_event {TYPE_1__* pmu; } ;
struct TYPE_2__ {int (* aux_output_match ) (struct perf_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  has_aux (struct perf_event*) ; 
 int stub1 (struct perf_event*) ; 

__attribute__((used)) static int
perf_aux_output_match(struct perf_event *event, struct perf_event *aux_event)
{
	if (!has_aux(aux_event))
		return 0;

	if (!event->pmu->aux_output_match)
		return 0;

	return event->pmu->aux_output_match(aux_event);
}