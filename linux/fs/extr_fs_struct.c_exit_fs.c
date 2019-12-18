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
struct task_struct {struct fs_struct* fs; } ;
struct fs_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_fs_struct (struct fs_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

void exit_fs(struct task_struct *tsk)
{
	struct fs_struct *fs = tsk->fs;

	if (fs) {
		int kill;
		task_lock(tsk);
		spin_lock(&fs->lock);
		tsk->fs = NULL;
		kill = !--fs->users;
		spin_unlock(&fs->lock);
		task_unlock(tsk);
		if (kill)
			free_fs_struct(fs);
	}
}