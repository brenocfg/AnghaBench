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
struct the_nilfs {int /*<<< orphan*/  ns_inode_lock; int /*<<< orphan*/  ns_dirty_files; int /*<<< orphan*/  ns_ndirtyblks; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_dirty; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_I_BUSY ; 
 int /*<<< orphan*/  NILFS_I_DIRTY ; 
 int /*<<< orphan*/  NILFS_I_QUEUED ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * igrab (struct inode*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_msg (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nilfs_set_file_dirty(struct inode *inode, unsigned int nr_dirty)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);
	struct the_nilfs *nilfs = inode->i_sb->s_fs_info;

	atomic_add(nr_dirty, &nilfs->ns_ndirtyblks);

	if (test_and_set_bit(NILFS_I_DIRTY, &ii->i_state))
		return 0;

	spin_lock(&nilfs->ns_inode_lock);
	if (!test_bit(NILFS_I_QUEUED, &ii->i_state) &&
	    !test_bit(NILFS_I_BUSY, &ii->i_state)) {
		/*
		 * Because this routine may race with nilfs_dispose_list(),
		 * we have to check NILFS_I_QUEUED here, too.
		 */
		if (list_empty(&ii->i_dirty) && igrab(inode) == NULL) {
			/*
			 * This will happen when somebody is freeing
			 * this inode.
			 */
			nilfs_msg(inode->i_sb, KERN_WARNING,
				  "cannot set file dirty (ino=%lu): the file is being freed",
				  inode->i_ino);
			spin_unlock(&nilfs->ns_inode_lock);
			return -EINVAL; /*
					 * NILFS_I_DIRTY may remain for
					 * freeing inode.
					 */
		}
		list_move_tail(&ii->i_dirty, &nilfs->ns_dirty_files);
		set_bit(NILFS_I_QUEUED, &ii->i_state);
	}
	spin_unlock(&nilfs->ns_inode_lock);
	return 0;
}