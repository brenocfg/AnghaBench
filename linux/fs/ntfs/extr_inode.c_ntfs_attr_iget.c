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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  test_t ;
struct inode {int i_state; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  set_t ;
typedef  int /*<<< orphan*/  ntfschar ;
struct TYPE_3__ {int /*<<< orphan*/  mft_no; int /*<<< orphan*/  name_len; int /*<<< orphan*/ * name; scalar_t__ type; } ;
typedef  TYPE_1__ ntfs_attr ;
typedef  scalar_t__ ATTR_TYPE ;

/* Variables and functions */
 scalar_t__ AT_INDEX_ALLOCATION ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int I_NEW ; 
 struct inode* iget5_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ ntfs_init_locked_inode ; 
 int ntfs_read_locked_attr_inode (struct inode*,struct inode*) ; 
 scalar_t__ ntfs_test_inode ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ntfs_attr_iget(struct inode *base_vi, ATTR_TYPE type,
		ntfschar *name, u32 name_len)
{
	struct inode *vi;
	int err;
	ntfs_attr na;

	/* Make sure no one calls ntfs_attr_iget() for indices. */
	BUG_ON(type == AT_INDEX_ALLOCATION);

	na.mft_no = base_vi->i_ino;
	na.type = type;
	na.name = name;
	na.name_len = name_len;

	vi = iget5_locked(base_vi->i_sb, na.mft_no, (test_t)ntfs_test_inode,
			(set_t)ntfs_init_locked_inode, &na);
	if (unlikely(!vi))
		return ERR_PTR(-ENOMEM);

	err = 0;

	/* If this is a freshly allocated inode, need to read it now. */
	if (vi->i_state & I_NEW) {
		err = ntfs_read_locked_attr_inode(base_vi, vi);
		unlock_new_inode(vi);
	}
	/*
	 * There is no point in keeping bad attribute inodes around. This also
	 * simplifies things in that we never need to check for bad attribute
	 * inodes elsewhere.
	 */
	if (unlikely(err)) {
		iput(vi);
		vi = ERR_PTR(err);
	}
	return vi;
}