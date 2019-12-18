#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct taskstats {int dummy; } ;
struct task_struct {TYPE_1__* sighand; struct signal_struct* signal; } ;
struct signal_struct {struct taskstats* stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct taskstats*) ; 
 struct taskstats* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskstats_cache ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 

__attribute__((used)) static struct taskstats *taskstats_tgid_alloc(struct task_struct *tsk)
{
	struct signal_struct *sig = tsk->signal;
	struct taskstats *stats;

	if (sig->stats || thread_group_empty(tsk))
		goto ret;

	/* No problem if kmem_cache_zalloc() fails */
	stats = kmem_cache_zalloc(taskstats_cache, GFP_KERNEL);

	spin_lock_irq(&tsk->sighand->siglock);
	if (!sig->stats) {
		sig->stats = stats;
		stats = NULL;
	}
	spin_unlock_irq(&tsk->sighand->siglock);

	if (stats)
		kmem_cache_free(taskstats_cache, stats);
ret:
	return sig->stats;
}