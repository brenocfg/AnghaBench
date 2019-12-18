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
struct task_struct {int /*<<< orphan*/ * pi_blocked_on; int /*<<< orphan*/ * pi_top_task; int /*<<< orphan*/  pi_waiters; int /*<<< orphan*/  pi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt_mutex_init_task(struct task_struct *p)
{
	raw_spin_lock_init(&p->pi_lock);
#ifdef CONFIG_RT_MUTEXES
	p->pi_waiters = RB_ROOT_CACHED;
	p->pi_top_task = NULL;
	p->pi_blocked_on = NULL;
#endif
}