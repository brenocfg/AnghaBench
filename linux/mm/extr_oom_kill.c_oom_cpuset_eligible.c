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
struct oom_control {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool oom_cpuset_eligible(struct task_struct *tsk, struct oom_control *oc)
{
	return true;
}