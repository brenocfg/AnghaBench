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
typedef  int /*<<< orphan*/  vm_flags_t ;
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;
struct user_struct {int dummy; } ;
struct inode {size_t i_size; int /*<<< orphan*/  i_flags; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  EPERM ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int HUGETLB_SHMFS_INODE ; 
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int S_IFREG ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  S_PRIVATE ; 
 struct file* alloc_file_pseudo (struct inode*,struct vfsmount*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_do_hugetlb_shm () ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 TYPE_1__* current ; 
 struct user_struct* current_user () ; 
 int get_hstate_idx (int) ; 
 int /*<<< orphan*/  hstate_inode (struct inode*) ; 
 size_t huge_page_shift (int /*<<< orphan*/ ) ; 
 scalar_t__ hugetlb_reserve_pages (struct inode*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlbfs_file_operations ; 
 struct inode* hugetlbfs_get_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct vfsmount** hugetlbfs_vfsmount ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 scalar_t__ user_shm_lock (size_t,struct user_struct*) ; 
 int /*<<< orphan*/  user_shm_unlock (size_t,struct user_struct*) ; 

struct file *hugetlb_file_setup(const char *name, size_t size,
				vm_flags_t acctflag, struct user_struct **user,
				int creat_flags, int page_size_log)
{
	struct inode *inode;
	struct vfsmount *mnt;
	int hstate_idx;
	struct file *file;

	hstate_idx = get_hstate_idx(page_size_log);
	if (hstate_idx < 0)
		return ERR_PTR(-ENODEV);

	*user = NULL;
	mnt = hugetlbfs_vfsmount[hstate_idx];
	if (!mnt)
		return ERR_PTR(-ENOENT);

	if (creat_flags == HUGETLB_SHMFS_INODE && !can_do_hugetlb_shm()) {
		*user = current_user();
		if (user_shm_lock(size, *user)) {
			task_lock(current);
			pr_warn_once("%s (%d): Using mlock ulimits for SHM_HUGETLB is deprecated\n",
				current->comm, current->pid);
			task_unlock(current);
		} else {
			*user = NULL;
			return ERR_PTR(-EPERM);
		}
	}

	file = ERR_PTR(-ENOSPC);
	inode = hugetlbfs_get_inode(mnt->mnt_sb, NULL, S_IFREG | S_IRWXUGO, 0);
	if (!inode)
		goto out;
	if (creat_flags == HUGETLB_SHMFS_INODE)
		inode->i_flags |= S_PRIVATE;

	inode->i_size = size;
	clear_nlink(inode);

	if (hugetlb_reserve_pages(inode, 0,
			size >> huge_page_shift(hstate_inode(inode)), NULL,
			acctflag))
		file = ERR_PTR(-ENOMEM);
	else
		file = alloc_file_pseudo(inode, mnt, name, O_RDWR,
					&hugetlbfs_file_operations);
	if (!IS_ERR(file))
		return file;

	iput(inode);
out:
	if (*user) {
		user_shm_unlock(size, *user);
		*user = NULL;
	}
	return file;
}