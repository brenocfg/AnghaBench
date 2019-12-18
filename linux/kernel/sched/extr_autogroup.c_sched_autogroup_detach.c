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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  autogroup_default ; 
 int /*<<< orphan*/  autogroup_move_group (struct task_struct*,int /*<<< orphan*/ *) ; 

void sched_autogroup_detach(struct task_struct *p)
{
	autogroup_move_group(p, &autogroup_default);
}