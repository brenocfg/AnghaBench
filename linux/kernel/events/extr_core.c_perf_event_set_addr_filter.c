#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nr_file_filters; } ;
struct perf_event {TYPE_1__ addr_filters; TYPE_3__* pmu; int /*<<< orphan*/  parent; TYPE_2__* ctx; } ;
struct TYPE_6__ {int (* addr_filters_validate ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filters ; 
 int /*<<< orphan*/  free_filters_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_addr_filters_splice (struct perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_addr_filters_apply ; 
 int /*<<< orphan*/  perf_event_for_each_child (struct perf_event*,int /*<<< orphan*/ ) ; 
 int perf_event_parse_addr_filter (struct perf_event*,char*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
perf_event_set_addr_filter(struct perf_event *event, char *filter_str)
{
	LIST_HEAD(filters);
	int ret;

	/*
	 * Since this is called in perf_ioctl() path, we're already holding
	 * ctx::mutex.
	 */
	lockdep_assert_held(&event->ctx->mutex);

	if (WARN_ON_ONCE(event->parent))
		return -EINVAL;

	ret = perf_event_parse_addr_filter(event, filter_str, &filters);
	if (ret)
		goto fail_clear_files;

	ret = event->pmu->addr_filters_validate(&filters);
	if (ret)
		goto fail_free_filters;

	/* remove existing filters, if any */
	perf_addr_filters_splice(event, &filters);

	/* install new filters */
	perf_event_for_each_child(event, perf_event_addr_filters_apply);

	return ret;

fail_free_filters:
	free_filters_list(&filters);

fail_clear_files:
	event->addr_filters.nr_file_filters = 0;

	return ret;
}