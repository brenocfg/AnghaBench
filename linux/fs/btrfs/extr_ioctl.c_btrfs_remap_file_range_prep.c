#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_sb; scalar_t__ i_size; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_7__ {scalar_t__ mnt; } ;
struct file {TYPE_3__ f_path; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_8__ {int flags; struct btrfs_root* root; } ;
struct TYPE_6__ {TYPE_1__* sb; } ;
struct TYPE_5__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 scalar_t__ ALIGN_DOWN (scalar_t__,scalar_t__) ; 
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 int EINVAL ; 
 int EROFS ; 
 int EXDEV ; 
 unsigned int REMAP_FILE_DEDUP ; 
 scalar_t__ btrfs_root_readonly (struct btrfs_root*) ; 
 int btrfs_wait_ordered_range (struct inode*,scalar_t__,scalar_t__) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_flush (int /*<<< orphan*/ ) ; 
 int generic_remap_file_range_prep (struct file*,scalar_t__,struct file*,scalar_t__,scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 

__attribute__((used)) static int btrfs_remap_file_range_prep(struct file *file_in, loff_t pos_in,
				       struct file *file_out, loff_t pos_out,
				       loff_t *len, unsigned int remap_flags)
{
	struct inode *inode_in = file_inode(file_in);
	struct inode *inode_out = file_inode(file_out);
	u64 bs = BTRFS_I(inode_out)->root->fs_info->sb->s_blocksize;
	bool same_inode = inode_out == inode_in;
	u64 wb_len;
	int ret;

	if (!(remap_flags & REMAP_FILE_DEDUP)) {
		struct btrfs_root *root_out = BTRFS_I(inode_out)->root;

		if (btrfs_root_readonly(root_out))
			return -EROFS;

		if (file_in->f_path.mnt != file_out->f_path.mnt ||
		    inode_in->i_sb != inode_out->i_sb)
			return -EXDEV;
	}

	/* don't make the dst file partly checksummed */
	if ((BTRFS_I(inode_in)->flags & BTRFS_INODE_NODATASUM) !=
	    (BTRFS_I(inode_out)->flags & BTRFS_INODE_NODATASUM)) {
		return -EINVAL;
	}

	/*
	 * Now that the inodes are locked, we need to start writeback ourselves
	 * and can not rely on the writeback from the VFS's generic helper
	 * generic_remap_file_range_prep() because:
	 *
	 * 1) For compression we must call filemap_fdatawrite_range() range
	 *    twice (btrfs_fdatawrite_range() does it for us), and the generic
	 *    helper only calls it once;
	 *
	 * 2) filemap_fdatawrite_range(), called by the generic helper only
	 *    waits for the writeback to complete, i.e. for IO to be done, and
	 *    not for the ordered extents to complete. We need to wait for them
	 *    to complete so that new file extent items are in the fs tree.
	 */
	if (*len == 0 && !(remap_flags & REMAP_FILE_DEDUP))
		wb_len = ALIGN(inode_in->i_size, bs) - ALIGN_DOWN(pos_in, bs);
	else
		wb_len = ALIGN(*len, bs);

	/*
	 * Since we don't lock ranges, wait for ongoing lockless dio writes (as
	 * any in progress could create its ordered extents after we wait for
	 * existing ordered extents below).
	 */
	inode_dio_wait(inode_in);
	if (!same_inode)
		inode_dio_wait(inode_out);

	/*
	 * Workaround to make sure NOCOW buffered write reach disk as NOCOW.
	 *
	 * Btrfs' back references do not have a block level granularity, they
	 * work at the whole extent level.
	 * NOCOW buffered write without data space reserved may not be able
	 * to fall back to CoW due to lack of data space, thus could cause
	 * data loss.
	 *
	 * Here we take a shortcut by flushing the whole inode, so that all
	 * nocow write should reach disk as nocow before we increase the
	 * reference of the extent. We could do better by only flushing NOCOW
	 * data, but that needs extra accounting.
	 *
	 * Also we don't need to check ASYNC_EXTENT, as async extent will be
	 * CoWed anyway, not affecting nocow part.
	 */
	ret = filemap_flush(inode_in->i_mapping);
	if (ret < 0)
		return ret;

	ret = btrfs_wait_ordered_range(inode_in, ALIGN_DOWN(pos_in, bs),
				       wb_len);
	if (ret < 0)
		return ret;
	ret = btrfs_wait_ordered_range(inode_out, ALIGN_DOWN(pos_out, bs),
				       wb_len);
	if (ret < 0)
		return ret;

	return generic_remap_file_range_prep(file_in, pos_in, file_out, pos_out,
					    len, remap_flags);
}