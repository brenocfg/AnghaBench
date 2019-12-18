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
struct trace_uprobe_filter {int /*<<< orphan*/  perf_events; int /*<<< orphan*/  nr_systemwide; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool uprobe_filter_is_empty(struct trace_uprobe_filter *filter)
{
	return !filter->nr_systemwide && list_empty(&filter->perf_events);
}