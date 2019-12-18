#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_event {int cpu; } ;
struct perf_addr_filter {int /*<<< orphan*/  entry; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int cpu_to_node (int) ; 
 struct perf_addr_filter* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static struct perf_addr_filter *
perf_addr_filter_new(struct perf_event *event, struct list_head *filters)
{
	int node = cpu_to_node(event->cpu == -1 ? 0 : event->cpu);
	struct perf_addr_filter *filter;

	filter = kzalloc_node(sizeof(*filter), GFP_KERNEL, node);
	if (!filter)
		return NULL;

	INIT_LIST_HEAD(&filter->entry);
	list_add_tail(&filter->entry, filters);

	return filter;
}