#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_9__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_8__ {void* tv_nsec; void* tv_sec; } ;
struct inode {int /*<<< orphan*/  i_generation; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; scalar_t__ i_rdev; int /*<<< orphan*/  i_mode; } ;
struct btrfs_inode_item {int /*<<< orphan*/  otime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  mutex; struct btrfs_inode_item inode_item; int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_12__ {scalar_t__ index_cnt; int /*<<< orphan*/  generation; TYPE_4__ i_otime; int /*<<< orphan*/  flags; int /*<<< orphan*/  last_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DELAYED_NODE_INODE_DIRTY ; 
 TYPE_5__* BTRFS_I (struct inode*) ; 
 int ENOENT ; 
 struct btrfs_delayed_node* btrfs_get_delayed_node (TYPE_5__*) ; 
 int /*<<< orphan*/  btrfs_i_size_write (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_flags (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_generation (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_gid (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_mode (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_nbytes (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_nlink (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_rdev (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_sequence (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_size (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_transid (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_stack_inode_uid (struct btrfs_inode_item*) ; 
 void* btrfs_stack_timespec_nsec (int /*<<< orphan*/ *) ; 
 void* btrfs_stack_timespec_sec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_iversion_queried (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_fill_inode(struct inode *inode, u32 *rdev)
{
	struct btrfs_delayed_node *delayed_node;
	struct btrfs_inode_item *inode_item;

	delayed_node = btrfs_get_delayed_node(BTRFS_I(inode));
	if (!delayed_node)
		return -ENOENT;

	mutex_lock(&delayed_node->mutex);
	if (!test_bit(BTRFS_DELAYED_NODE_INODE_DIRTY, &delayed_node->flags)) {
		mutex_unlock(&delayed_node->mutex);
		btrfs_release_delayed_node(delayed_node);
		return -ENOENT;
	}

	inode_item = &delayed_node->inode_item;

	i_uid_write(inode, btrfs_stack_inode_uid(inode_item));
	i_gid_write(inode, btrfs_stack_inode_gid(inode_item));
	btrfs_i_size_write(BTRFS_I(inode), btrfs_stack_inode_size(inode_item));
	inode->i_mode = btrfs_stack_inode_mode(inode_item);
	set_nlink(inode, btrfs_stack_inode_nlink(inode_item));
	inode_set_bytes(inode, btrfs_stack_inode_nbytes(inode_item));
	BTRFS_I(inode)->generation = btrfs_stack_inode_generation(inode_item);
        BTRFS_I(inode)->last_trans = btrfs_stack_inode_transid(inode_item);

	inode_set_iversion_queried(inode,
				   btrfs_stack_inode_sequence(inode_item));
	inode->i_rdev = 0;
	*rdev = btrfs_stack_inode_rdev(inode_item);
	BTRFS_I(inode)->flags = btrfs_stack_inode_flags(inode_item);

	inode->i_atime.tv_sec = btrfs_stack_timespec_sec(&inode_item->atime);
	inode->i_atime.tv_nsec = btrfs_stack_timespec_nsec(&inode_item->atime);

	inode->i_mtime.tv_sec = btrfs_stack_timespec_sec(&inode_item->mtime);
	inode->i_mtime.tv_nsec = btrfs_stack_timespec_nsec(&inode_item->mtime);

	inode->i_ctime.tv_sec = btrfs_stack_timespec_sec(&inode_item->ctime);
	inode->i_ctime.tv_nsec = btrfs_stack_timespec_nsec(&inode_item->ctime);

	BTRFS_I(inode)->i_otime.tv_sec =
		btrfs_stack_timespec_sec(&inode_item->otime);
	BTRFS_I(inode)->i_otime.tv_nsec =
		btrfs_stack_timespec_nsec(&inode_item->otime);

	inode->i_generation = BTRFS_I(inode)->generation;
	BTRFS_I(inode)->index_cnt = (u64)-1;

	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	return 0;
}