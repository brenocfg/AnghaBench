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
struct perf_event_groups {int dummy; } ;
struct perf_event_context {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 struct perf_event_groups* get_event_groups (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_groups_delete (struct perf_event_groups*,struct perf_event*) ; 

__attribute__((used)) static void
del_event_from_groups(struct perf_event *event, struct perf_event_context *ctx)
{
	struct perf_event_groups *groups;

	groups = get_event_groups(event, ctx);
	perf_event_groups_delete(groups, event);
}