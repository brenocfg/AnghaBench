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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_state {unsigned int state; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; } ;
struct btrfs_inode {scalar_t__ delalloc_bytes; int /*<<< orphan*/  lock; scalar_t__ new_delalloc_bytes; int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  vfs_inode; struct btrfs_root* root; scalar_t__ defrag_bytes; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delalloc_batch; int /*<<< orphan*/  delalloc_bytes; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_DATA_RELOC_TREE_OBJECTID ; 
 struct btrfs_inode* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_IN_DELALLOC_LIST ; 
 unsigned int EXTENT_CLEAR_DATA_RESV ; 
 unsigned int EXTENT_CLEAR_META_RESV ; 
 unsigned int EXTENT_DEFRAG ; 
 unsigned int EXTENT_DELALLOC ; 
 unsigned int EXTENT_DELALLOC_NEW ; 
 int EXTENT_NORESERVE ; 
 int /*<<< orphan*/  btrfs_del_delalloc_inode (struct btrfs_root*,struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_metadata (struct btrfs_inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space_noquota (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_is_free_space_inode (struct btrfs_inode*) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (struct btrfs_inode*,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_max_extents (scalar_t__) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_clear_delalloc_extent(struct inode *vfs_inode,
				 struct extent_state *state, unsigned *bits)
{
	struct btrfs_inode *inode = BTRFS_I(vfs_inode);
	struct btrfs_fs_info *fs_info = btrfs_sb(vfs_inode->i_sb);
	u64 len = state->end + 1 - state->start;
	u32 num_extents = count_max_extents(len);

	if ((state->state & EXTENT_DEFRAG) && (*bits & EXTENT_DEFRAG)) {
		spin_lock(&inode->lock);
		inode->defrag_bytes -= len;
		spin_unlock(&inode->lock);
	}

	/*
	 * set_bit and clear bit hooks normally require _irqsave/restore
	 * but in this case, we are only testing for the DELALLOC
	 * bit, which is only set or cleared with irqs on
	 */
	if ((state->state & EXTENT_DELALLOC) && (*bits & EXTENT_DELALLOC)) {
		struct btrfs_root *root = inode->root;
		bool do_list = !btrfs_is_free_space_inode(inode);

		spin_lock(&inode->lock);
		btrfs_mod_outstanding_extents(inode, -num_extents);
		spin_unlock(&inode->lock);

		/*
		 * We don't reserve metadata space for space cache inodes so we
		 * don't need to call delalloc_release_metadata if there is an
		 * error.
		 */
		if (*bits & EXTENT_CLEAR_META_RESV &&
		    root != fs_info->tree_root)
			btrfs_delalloc_release_metadata(inode, len, false);

		/* For sanity tests. */
		if (btrfs_is_testing(fs_info))
			return;

		if (root->root_key.objectid != BTRFS_DATA_RELOC_TREE_OBJECTID &&
		    do_list && !(state->state & EXTENT_NORESERVE) &&
		    (*bits & EXTENT_CLEAR_DATA_RESV))
			btrfs_free_reserved_data_space_noquota(
					&inode->vfs_inode,
					state->start, len);

		percpu_counter_add_batch(&fs_info->delalloc_bytes, -len,
					 fs_info->delalloc_batch);
		spin_lock(&inode->lock);
		inode->delalloc_bytes -= len;
		if (do_list && inode->delalloc_bytes == 0 &&
		    test_bit(BTRFS_INODE_IN_DELALLOC_LIST,
					&inode->runtime_flags))
			btrfs_del_delalloc_inode(root, inode);
		spin_unlock(&inode->lock);
	}

	if ((state->state & EXTENT_DELALLOC_NEW) &&
	    (*bits & EXTENT_DELALLOC_NEW)) {
		spin_lock(&inode->lock);
		ASSERT(inode->new_delalloc_bytes >= len);
		inode->new_delalloc_bytes -= len;
		spin_unlock(&inode->lock);
	}
}