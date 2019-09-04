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
struct tasklet_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASKLET_SOFTIRQ ; 
 int /*<<< orphan*/  __tasklet_schedule_common (struct tasklet_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_vec ; 

void __tasklet_schedule(struct tasklet_struct *t)
{
	__tasklet_schedule_common(t, &tasklet_vec,
				  TASKLET_SOFTIRQ);
}