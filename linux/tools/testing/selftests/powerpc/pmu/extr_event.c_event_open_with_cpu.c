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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_NO_GROUP ; 
 int /*<<< orphan*/  PERF_NO_PID ; 
 int event_open_with_options (struct event*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int event_open_with_cpu(struct event *e, int cpu)
{
	return event_open_with_options(e, PERF_NO_PID, cpu, PERF_NO_GROUP);
}