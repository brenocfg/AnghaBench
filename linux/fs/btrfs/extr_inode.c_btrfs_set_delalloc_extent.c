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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_state {unsigned int state; scalar_t__ start; scalar_t__ end; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delalloc_batch; int /*<<< orphan*/  delalloc_bytes; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  new_delalloc_bytes; int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  defrag_bytes; int /*<<< orphan*/  delalloc_bytes; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_IN_DELALLOC_LIST ; 
 unsigned int EXTENT_DEFRAG ; 
 unsigned int EXTENT_DELALLOC ; 
 unsigned int EXTENT_DELALLOC_NEW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_add_delalloc_inodes (struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_is_free_space_inode (TYPE_1__*) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_max_extents (scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_set_delalloc_extent(struct inode *inode, struct extent_state *state,
			       unsigned *bits)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

	if ((*bits & EXTENT_DEFRAG) && !(*bits & EXTENT_DELALLOC))
		WARN_ON(1);
	/*
	 * set_bit and clear bit hooks normally require _irqsave/restore
	 * but in this case, we are only testing for the DELALLOC
	 * bit, which is only set or cleared with irqs on
	 */
	if (!(state->state & EXTENT_DELALLOC) && (*bits & EXTENT_DELALLOC)) {
		struct btrfs_root *root = BTRFS_I(inode)->root;
		u64 len = state->end + 1 - state->start;
		u32 num_extents = count_max_extents(len);
		bool do_list = !btrfs_is_free_space_inode(BTRFS_I(inode));

		spin_lock(&BTRFS_I(inode)->lock);
		btrfs_mod_outstanding_extents(BTRFS_I(inode), num_extents);
		spin_unlock(&BTRFS_I(inode)->lock);

		/* For sanity tests */
		if (btrfs_is_testing(fs_info))
			return;

		percpu_counter_add_batch(&fs_info->delalloc_bytes, len,
					 fs_info->delalloc_batch);
		spin_lock(&BTRFS_I(inode)->lock);
		BTRFS_I(inode)->delalloc_bytes += len;
		if (*bits & EXTENT_DEFRAG)
			BTRFS_I(inode)->defrag_bytes += len;
		if (do_list && !test_bit(BTRFS_INODE_IN_DELALLOC_LIST,
					 &BTRFS_I(inode)->runtime_flags))
			btrfs_add_delalloc_inodes(root, inode);
		spin_unlock(&BTRFS_I(inode)->lock);
	}

	if (!(state->state & EXTENT_DELALLOC_NEW) &&
	    (*bits & EXTENT_DELALLOC_NEW)) {
		spin_lock(&BTRFS_I(inode)->lock);
		BTRFS_I(inode)->new_delalloc_bytes += state->end + 1 -
			state->start;
		spin_unlock(&BTRFS_I(inode)->lock);
	}
}