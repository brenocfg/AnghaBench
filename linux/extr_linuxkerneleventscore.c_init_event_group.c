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
struct perf_event {scalar_t__ group_index; int /*<<< orphan*/  group_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_event_group(struct perf_event *event)
{
	RB_CLEAR_NODE(&event->group_node);
	event->group_index = 0;
}