#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fs_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; } ;
struct TYPE_4__ {struct fs_struct* fs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fs_struct* copy_fs_struct (struct fs_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  free_fs_struct (struct fs_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

int unshare_fs_struct(void)
{
	struct fs_struct *fs = current->fs;
	struct fs_struct *new_fs = copy_fs_struct(fs);
	int kill;

	if (!new_fs)
		return -ENOMEM;

	task_lock(current);
	spin_lock(&fs->lock);
	kill = !--fs->users;
	current->fs = new_fs;
	spin_unlock(&fs->lock);
	task_unlock(current);

	if (kill)
		free_fs_struct(fs);

	return 0;
}