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
struct f2fs_sb_info {struct f2fs_gc_kthread* gc_thread; } ;
struct f2fs_gc_kthread {int /*<<< orphan*/  f2fs_gc_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct f2fs_gc_kthread*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

void f2fs_stop_gc_thread(struct f2fs_sb_info *sbi)
{
	struct f2fs_gc_kthread *gc_th = sbi->gc_thread;
	if (!gc_th)
		return;
	kthread_stop(gc_th->f2fs_gc_task);
	kfree(gc_th);
	sbi->gc_thread = NULL;
}