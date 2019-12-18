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
 scalar_t__ lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  signal_wake_up (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static void fake_signal_wake_up(struct task_struct *p)
{
	unsigned long flags;

	if (lock_task_sighand(p, &flags)) {
		signal_wake_up(p, 0);
		unlock_task_sighand(p, &flags);
	}
}