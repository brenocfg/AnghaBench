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
typedef  int u64 ;
struct timechart {int dummy; } ;
struct per_pid {TYPE_1__* current; } ;
struct TYPE_2__ {scalar_t__ state; int state_since; } ;

/* Variables and functions */
 scalar_t__ TYPE_BLOCKED ; 
 scalar_t__ TYPE_NONE ; 
 scalar_t__ TYPE_RUNNING ; 
 scalar_t__ TYPE_WAITING ; 
 struct per_pid* find_create_pid (struct timechart*,int) ; 
 int /*<<< orphan*/  pid_put_sample (struct timechart*,int,scalar_t__,int,int,int,char const*) ; 

__attribute__((used)) static void sched_switch(struct timechart *tchart, int cpu, u64 timestamp,
			 int prev_pid, int next_pid, u64 prev_state,
			 const char *backtrace)
{
	struct per_pid *p = NULL, *prev_p;

	prev_p = find_create_pid(tchart, prev_pid);

	p = find_create_pid(tchart, next_pid);

	if (prev_p->current && prev_p->current->state != TYPE_NONE)
		pid_put_sample(tchart, prev_pid, TYPE_RUNNING, cpu,
			       prev_p->current->state_since, timestamp,
			       backtrace);
	if (p && p->current) {
		if (p->current->state != TYPE_NONE)
			pid_put_sample(tchart, next_pid, p->current->state, cpu,
				       p->current->state_since, timestamp,
				       backtrace);

		p->current->state_since = timestamp;
		p->current->state = TYPE_RUNNING;
	}

	if (prev_p->current) {
		prev_p->current->state = TYPE_NONE;
		prev_p->current->state_since = timestamp;
		if (prev_state & 2)
			prev_p->current->state = TYPE_BLOCKED;
		if (prev_state == 0)
			prev_p->current->state = TYPE_WAITING;
	}
}