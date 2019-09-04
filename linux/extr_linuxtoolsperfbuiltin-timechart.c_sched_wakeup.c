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
typedef  int u8 ;
typedef  void* u64 ;
struct wake_event {int waker; char const* backtrace; int wakee; struct wake_event* next; void* time; } ;
struct timechart {struct wake_event* wake_events; } ;
struct per_pid {TYPE_1__* current; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {scalar_t__ state; void* state_since; } ;

/* Variables and functions */
 int TRACE_FLAG_HARDIRQ ; 
 int TRACE_FLAG_SOFTIRQ ; 
 scalar_t__ TYPE_BLOCKED ; 
 scalar_t__ TYPE_NONE ; 
 void* TYPE_WAITING ; 
 struct per_pid* find_create_pid (struct timechart*,int) ; 
 int /*<<< orphan*/  pid_put_sample (struct timechart*,int /*<<< orphan*/ ,scalar_t__,int,void*,void*,int /*<<< orphan*/ *) ; 
 struct wake_event* zalloc (int) ; 

__attribute__((used)) static void sched_wakeup(struct timechart *tchart, int cpu, u64 timestamp,
			 int waker, int wakee, u8 flags, const char *backtrace)
{
	struct per_pid *p;
	struct wake_event *we = zalloc(sizeof(*we));

	if (!we)
		return;

	we->time = timestamp;
	we->waker = waker;
	we->backtrace = backtrace;

	if ((flags & TRACE_FLAG_HARDIRQ) || (flags & TRACE_FLAG_SOFTIRQ))
		we->waker = -1;

	we->wakee = wakee;
	we->next = tchart->wake_events;
	tchart->wake_events = we;
	p = find_create_pid(tchart, we->wakee);

	if (p && p->current && p->current->state == TYPE_NONE) {
		p->current->state_since = timestamp;
		p->current->state = TYPE_WAITING;
	}
	if (p && p->current && p->current->state == TYPE_BLOCKED) {
		pid_put_sample(tchart, p->pid, p->current->state, cpu,
			       p->current->state_since, timestamp, NULL);
		p->current->state_since = timestamp;
		p->current->state = TYPE_WAITING;
	}
}