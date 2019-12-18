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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_NO_CPU ; 
 int /*<<< orphan*/  PERF_NO_GROUP ; 
 int event_open_with_options (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int event_open_with_pid(struct event *e, pid_t pid)
{
	return event_open_with_options(e, pid, PERF_NO_CPU, PERF_NO_GROUP);
}