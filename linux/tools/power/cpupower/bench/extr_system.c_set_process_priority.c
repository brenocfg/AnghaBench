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
struct sched_param {int sched_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEDULER ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  stderr ; 

int set_process_priority(int priority)
{
	struct sched_param param;

	dprintf("set scheduler priority to %i\n", priority);

	param.sched_priority = priority;

	if (sched_setscheduler(0, SCHEDULER, &param) < 0) {
		perror("sched_setscheduler");
		fprintf(stderr, "warning: unable to set scheduler priority\n");
		return -1;
	}

	return 0;
}