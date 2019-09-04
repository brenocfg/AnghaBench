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
struct task_struct {int /*<<< orphan*/  mems_allowed; } ;

/* Variables and functions */
 int nodes_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cpuset_mems_allowed_intersects(const struct task_struct *tsk1,
				   const struct task_struct *tsk2)
{
	return nodes_intersects(tsk1->mems_allowed, tsk2->mems_allowed);
}