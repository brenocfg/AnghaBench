#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* rlim_max; void* rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  RLIMIT_MSGQUEUE ; 
 void* RLIM_INFINITY ; 
 TYPE_1__ cur_limits ; 
 int cur_max_msgs ; 
 int cur_max_msgsize ; 
 int cur_nice ; 
 int get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_msgs ; 
 int /*<<< orphan*/  max_msgsize ; 
 scalar_t__ setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 
 scalar_t__ try_set (int /*<<< orphan*/ ,int) ; 

void increase_limits(void)
{
	cur_limits.rlim_cur = RLIM_INFINITY;
	cur_limits.rlim_max = RLIM_INFINITY;
	setr(RLIMIT_MSGQUEUE, &cur_limits);
	while (try_set(max_msgs, cur_max_msgs += 10))
		;
	cur_max_msgs = get(max_msgs);
	while (try_set(max_msgsize, cur_max_msgsize += 1024))
		;
	cur_max_msgsize = get(max_msgsize);
	if (setpriority(PRIO_PROCESS, 0, -20) != 0)
		shutdown(2, "setpriority()", __LINE__);
	cur_nice = -20;
}