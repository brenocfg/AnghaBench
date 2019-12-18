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
struct task_struct {int dummy; } ;
struct inode {unsigned int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 unsigned int S_IFLNK ; 
 unsigned int S_IRUSR ; 
 scalar_t__ S_ISLNK (unsigned int) ; 
 unsigned int S_IWUSR ; 
 unsigned int S_IXUSR ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  task_dump_owner (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tid_fd_update_inode(struct task_struct *task, struct inode *inode,
				fmode_t f_mode)
{
	task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);

	if (S_ISLNK(inode->i_mode)) {
		unsigned i_mode = S_IFLNK;
		if (f_mode & FMODE_READ)
			i_mode |= S_IRUSR | S_IXUSR;
		if (f_mode & FMODE_WRITE)
			i_mode |= S_IWUSR | S_IXUSR;
		inode->i_mode = i_mode;
	}
	security_task_to_inode(task, inode);
}