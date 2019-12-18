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
struct signal_struct {int /*<<< orphan*/  autogroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  autogroup_task_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 

void sched_autogroup_fork(struct signal_struct *sig)
{
	sig->autogroup = autogroup_task_get(current);
}