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
typedef  size_t u64 ;
struct TYPE_2__ {size_t config; } ;
struct perf_event {int /*<<< orphan*/  parent; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * perf_swevent_enabled ; 
 int /*<<< orphan*/  static_key_slow_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swevent_hlist_put () ; 

__attribute__((used)) static void sw_perf_event_destroy(struct perf_event *event)
{
	u64 event_id = event->attr.config;

	WARN_ON(event->parent);

	static_key_slow_dec(&perf_swevent_enabled[event_id]);
	swevent_hlist_put();
}