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
struct jffs2_sb_info {int /*<<< orphan*/  alloc_sem; int /*<<< orphan*/  erase_completion_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  jffs2_dbg (int,char*) ; 
 int /*<<< orphan*/  jffs2_garbage_collect_trigger (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void jffs2_complete_reservation(struct jffs2_sb_info *c)
{
	jffs2_dbg(1, "jffs2_complete_reservation()\n");
	spin_lock(&c->erase_completion_lock);
	jffs2_garbage_collect_trigger(c);
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->alloc_sem);
}