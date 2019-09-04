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
typedef  void* u64 ;
struct inode_defrag {int cycled; int /*<<< orphan*/  last_offset; int /*<<< orphan*/  transid; int /*<<< orphan*/  ino; int /*<<< orphan*/  root; } ;
struct inode {int dummy; } ;
typedef  struct inode btrfs_root ;
struct btrfs_key {void* offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_ioctl_defrag_range_args {int /*<<< orphan*/  start; void* len; } ;
struct btrfs_fs_info {int /*<<< orphan*/  subvol_srcu; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  range ;
struct TYPE_3__ {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int BTRFS_DEFRAG_BATCH ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_IN_DEFRAG ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int btrfs_defrag_file (struct inode*,int /*<<< orphan*/ *,struct btrfs_ioctl_defrag_range_args*,int /*<<< orphan*/ ,int) ; 
 struct inode* btrfs_iget (int /*<<< orphan*/ ,struct btrfs_key*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_inode_defrag_cachep ; 
 struct inode* btrfs_read_fs_root_no_name (struct btrfs_fs_info*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_requeue_inode_defrag (TYPE_1__*,struct inode_defrag*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inode_defrag*) ; 
 int /*<<< orphan*/  memset (struct btrfs_ioctl_defrag_range_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write (int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __btrfs_run_defrag_inode(struct btrfs_fs_info *fs_info,
				    struct inode_defrag *defrag)
{
	struct btrfs_root *inode_root;
	struct inode *inode;
	struct btrfs_key key;
	struct btrfs_ioctl_defrag_range_args range;
	int num_defrag;
	int index;
	int ret;

	/* get the inode */
	key.objectid = defrag->root;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = (u64)-1;

	index = srcu_read_lock(&fs_info->subvol_srcu);

	inode_root = btrfs_read_fs_root_no_name(fs_info, &key);
	if (IS_ERR(inode_root)) {
		ret = PTR_ERR(inode_root);
		goto cleanup;
	}

	key.objectid = defrag->ino;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	inode = btrfs_iget(fs_info->sb, &key, inode_root, NULL);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		goto cleanup;
	}
	srcu_read_unlock(&fs_info->subvol_srcu, index);

	/* do a chunk of defrag */
	clear_bit(BTRFS_INODE_IN_DEFRAG, &BTRFS_I(inode)->runtime_flags);
	memset(&range, 0, sizeof(range));
	range.len = (u64)-1;
	range.start = defrag->last_offset;

	sb_start_write(fs_info->sb);
	num_defrag = btrfs_defrag_file(inode, NULL, &range, defrag->transid,
				       BTRFS_DEFRAG_BATCH);
	sb_end_write(fs_info->sb);
	/*
	 * if we filled the whole defrag batch, there
	 * must be more work to do.  Queue this defrag
	 * again
	 */
	if (num_defrag == BTRFS_DEFRAG_BATCH) {
		defrag->last_offset = range.start;
		btrfs_requeue_inode_defrag(BTRFS_I(inode), defrag);
	} else if (defrag->last_offset && !defrag->cycled) {
		/*
		 * we didn't fill our defrag batch, but
		 * we didn't start at zero.  Make sure we loop
		 * around to the start of the file.
		 */
		defrag->last_offset = 0;
		defrag->cycled = 1;
		btrfs_requeue_inode_defrag(BTRFS_I(inode), defrag);
	} else {
		kmem_cache_free(btrfs_inode_defrag_cachep, defrag);
	}

	iput(inode);
	return 0;
cleanup:
	srcu_read_unlock(&fs_info->subvol_srcu, index);
	kmem_cache_free(btrfs_inode_defrag_cachep, defrag);
	return ret;
}