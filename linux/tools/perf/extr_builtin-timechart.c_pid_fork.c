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
typedef  void* u64 ;
struct timechart {int dummy; } ;
struct per_pid {int ppid; TYPE_1__* current; void* start_time; } ;
struct TYPE_2__ {void* state_since; void* start_time; scalar_t__ comm; } ;

/* Variables and functions */
 struct per_pid* find_create_pid (struct timechart*,int) ; 
 int /*<<< orphan*/  pid_set_comm (struct timechart*,int,scalar_t__) ; 

__attribute__((used)) static void pid_fork(struct timechart *tchart, int pid, int ppid, u64 timestamp)
{
	struct per_pid *p, *pp;
	p = find_create_pid(tchart, pid);
	pp = find_create_pid(tchart, ppid);
	p->ppid = ppid;
	if (pp->current && pp->current->comm && !p->current)
		pid_set_comm(tchart, pid, pp->current->comm);

	p->start_time = timestamp;
	if (p->current && !p->current->start_time) {
		p->current->start_time = timestamp;
		p->current->state_since = timestamp;
	}
}