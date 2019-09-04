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
struct perf_event {int dummy; } ;
struct l3cache_event_ops {int dummy; } ;

/* Variables and functions */
 struct l3cache_event_ops const event_ops_long ; 
 struct l3cache_event_ops const event_ops_std ; 
 scalar_t__ event_uses_long_counter (struct perf_event*) ; 

__attribute__((used)) static
const struct l3cache_event_ops *l3cache_event_get_ops(struct perf_event *event)
{
	if (event_uses_long_counter(event))
		return &event_ops_long;
	else
		return &event_ops_std;
}