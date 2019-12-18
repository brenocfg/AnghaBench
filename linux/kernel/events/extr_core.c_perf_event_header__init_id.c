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
struct perf_sample_data {int dummy; } ;
struct perf_event_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ sample_id_all; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_header__init_id (struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 

void perf_event_header__init_id(struct perf_event_header *header,
				struct perf_sample_data *data,
				struct perf_event *event)
{
	if (event->attr.sample_id_all)
		__perf_event_header__init_id(header, data, event);
}