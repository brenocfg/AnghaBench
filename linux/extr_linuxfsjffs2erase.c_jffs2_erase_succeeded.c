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
struct jffs2_sb_info {int /*<<< orphan*/  erase_wait; int /*<<< orphan*/  erase_free_sem; int /*<<< orphan*/  erase_completion_lock; int /*<<< orphan*/  erase_complete_list; } ;
struct jffs2_eraseblock {int /*<<< orphan*/  list; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  jffs2_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_garbage_collect_trigger (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jffs2_erase_succeeded(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb)
{
	jffs2_dbg(1, "Erase completed successfully at 0x%08x\n", jeb->offset);
	mutex_lock(&c->erase_free_sem);
	spin_lock(&c->erase_completion_lock);
	list_move_tail(&jeb->list, &c->erase_complete_list);
	/* Wake the GC thread to mark them clean */
	jffs2_garbage_collect_trigger(c);
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_free_sem);
	wake_up(&c->erase_wait);
}