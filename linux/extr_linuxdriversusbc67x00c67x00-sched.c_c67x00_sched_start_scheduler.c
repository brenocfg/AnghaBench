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
struct c67x00_hcd {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  c67x00_sched_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int c67x00_sched_start_scheduler(struct c67x00_hcd *c67x00)
{
	tasklet_init(&c67x00->tasklet, c67x00_sched_tasklet,
		     (unsigned long)c67x00);
	return 0;
}