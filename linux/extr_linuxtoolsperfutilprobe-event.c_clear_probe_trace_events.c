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
struct probe_trace_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_probe_trace_event (struct probe_trace_event*) ; 

__attribute__((used)) static void clear_probe_trace_events(struct probe_trace_event *tevs, int ntevs)
{
	int i;

	for (i = 0; i < ntevs; i++)
		clear_probe_trace_event(tevs + i);
}