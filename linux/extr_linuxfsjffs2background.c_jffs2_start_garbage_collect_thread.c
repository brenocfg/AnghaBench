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
struct task_struct {int pid; } ;
struct jffs2_sb_info {int /*<<< orphan*/  gc_thread_start; int /*<<< orphan*/  gc_thread_exit; TYPE_1__* mtd; int /*<<< orphan*/  gc_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,int) ; 
 int /*<<< orphan*/  jffs2_garbage_collect_thread ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct jffs2_sb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int jffs2_start_garbage_collect_thread(struct jffs2_sb_info *c)
{
	struct task_struct *tsk;
	int ret = 0;

	BUG_ON(c->gc_task);

	init_completion(&c->gc_thread_start);
	init_completion(&c->gc_thread_exit);

	tsk = kthread_run(jffs2_garbage_collect_thread, c, "jffs2_gcd_mtd%d", c->mtd->index);
	if (IS_ERR(tsk)) {
		pr_warn("fork failed for JFFS2 garbage collect thread: %ld\n",
			-PTR_ERR(tsk));
		complete(&c->gc_thread_exit);
		ret = PTR_ERR(tsk);
	} else {
		/* Wait for it... */
		jffs2_dbg(1, "Garbage collect thread is pid %d\n", tsk->pid);
		wait_for_completion(&c->gc_thread_start);
		ret = tsk->pid;
	}

	return ret;
}