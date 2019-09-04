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
struct mqueue_inode_info {scalar_t__ notify_owner; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 struct mqueue_inode_info* MQUEUE_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  remove_notification (struct mqueue_inode_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ task_tgid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mqueue_flush_file(struct file *filp, fl_owner_t id)
{
	struct mqueue_inode_info *info = MQUEUE_I(file_inode(filp));

	spin_lock(&info->lock);
	if (task_tgid(current) == info->notify_owner)
		remove_notification(info);

	spin_unlock(&info->lock);
	return 0;
}