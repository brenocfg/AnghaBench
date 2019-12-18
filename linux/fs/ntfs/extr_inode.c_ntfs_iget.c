#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_t ;
struct super_block {int dummy; } ;
struct inode {int i_state; } ;
typedef  int /*<<< orphan*/  set_t ;
struct TYPE_3__ {unsigned long mft_no; scalar_t__ name_len; int /*<<< orphan*/ * name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ntfs_attr ;

/* Variables and functions */
 int /*<<< orphan*/  AT_UNUSED ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ ntfs_init_locked_inode ; 
 int ntfs_read_locked_inode (struct inode*) ; 
 scalar_t__ ntfs_test_inode ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ntfs_iget(struct super_block *sb, unsigned long mft_no)
{
	struct inode *vi;
	int err;
	ntfs_attr na;

	na.mft_no = mft_no;
	na.type = AT_UNUSED;
	na.name = NULL;
	na.name_len = 0;

	vi = iget5_locked(sb, mft_no, (test_t)ntfs_test_inode,
			(set_t)ntfs_init_locked_inode, &na);
	if (unlikely(!vi))
		return ERR_PTR(-ENOMEM);

	err = 0;

	/* If this is a freshly allocated inode, need to read it now. */
	if (vi->i_state & I_NEW) {
		err = ntfs_read_locked_inode(vi);
		unlock_new_inode(vi);
	}
	/*
	 * There is no point in keeping bad inodes around if the failure was
	 * due to ENOMEM. We want to be able to retry again later.
	 */
	if (unlikely(err == -ENOMEM)) {
		iput(vi);
		vi = ERR_PTR(err);
	}
	return vi;
}