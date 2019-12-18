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
struct jffs2_sb_info {int /*<<< orphan*/  gc_thread_exit; int /*<<< orphan*/  erase_completion_lock; TYPE_1__* gc_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void jffs2_stop_garbage_collect_thread(struct jffs2_sb_info *c)
{
	int wait = 0;
	spin_lock(&c->erase_completion_lock);
	if (c->gc_task) {
		jffs2_dbg(1, "Killing GC task %d\n", c->gc_task->pid);
		send_sig(SIGKILL, c->gc_task, 1);
		wait = 1;
	}
	spin_unlock(&c->erase_completion_lock);
	if (wait)
		wait_for_completion(&c->gc_thread_exit);
}