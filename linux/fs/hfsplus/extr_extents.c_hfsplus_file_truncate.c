#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct page {int dummy; } ;
struct inode {int i_size; struct address_space* i_mapping; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct hfsplus_inode_info {int phys_size; void* first_blocks; int extent_state; int fs_blocks; int /*<<< orphan*/  extents_lock; void* alloc_blocks; void* cached_blocks; void* cached_start; int /*<<< orphan*/  cached_extents; int /*<<< orphan*/  first_extents; } ;
struct hfs_find_data {TYPE_1__* tree; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
struct TYPE_4__ {int alloc_blksz; int alloc_blksz_shift; int /*<<< orphan*/  ext_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  tree_lock; } ;

/* Variables and functions */
 int HFSPLUS_EXT_DIRTY ; 
 int HFSPLUS_EXT_NEW ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 int /*<<< orphan*/  HFSPLUS_I_ALLOC_DIRTY ; 
 TYPE_2__* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  INODE ; 
 int __hfsplus_ext_cache_extent (struct hfs_find_data*,struct inode*,void*) ; 
 int /*<<< orphan*/  hfs_brec_remove (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long long,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfsplus_dump_extent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsplus_free_extents (struct super_block*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  hfsplus_mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pagecache_write_begin (int /*<<< orphan*/ *,struct address_space*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**,void**) ; 
 int pagecache_write_end (int /*<<< orphan*/ *,struct address_space*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,void*) ; 

void hfsplus_file_truncate(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	struct hfs_find_data fd;
	u32 alloc_cnt, blk_cnt, start;
	int res;

	hfs_dbg(INODE, "truncate: %lu, %llu -> %llu\n",
		inode->i_ino, (long long)hip->phys_size, inode->i_size);

	if (inode->i_size > hip->phys_size) {
		struct address_space *mapping = inode->i_mapping;
		struct page *page;
		void *fsdata;
		loff_t size = inode->i_size;

		res = pagecache_write_begin(NULL, mapping, size, 0, 0,
					    &page, &fsdata);
		if (res)
			return;
		res = pagecache_write_end(NULL, mapping, size,
			0, 0, page, fsdata);
		if (res < 0)
			return;
		mark_inode_dirty(inode);
		return;
	} else if (inode->i_size == hip->phys_size)
		return;

	blk_cnt = (inode->i_size + HFSPLUS_SB(sb)->alloc_blksz - 1) >>
			HFSPLUS_SB(sb)->alloc_blksz_shift;

	mutex_lock(&hip->extents_lock);

	alloc_cnt = hip->alloc_blocks;
	if (blk_cnt == alloc_cnt)
		goto out_unlock;

	res = hfs_find_init(HFSPLUS_SB(sb)->ext_tree, &fd);
	if (res) {
		mutex_unlock(&hip->extents_lock);
		/* XXX: We lack error handling of hfsplus_file_truncate() */
		return;
	}
	while (1) {
		if (alloc_cnt == hip->first_blocks) {
			mutex_unlock(&fd.tree->tree_lock);
			hfsplus_free_extents(sb, hip->first_extents,
					     alloc_cnt, alloc_cnt - blk_cnt);
			hfsplus_dump_extent(hip->first_extents);
			hip->first_blocks = blk_cnt;
			mutex_lock(&fd.tree->tree_lock);
			break;
		}
		res = __hfsplus_ext_cache_extent(&fd, inode, alloc_cnt);
		if (res)
			break;
		hfs_brec_remove(&fd);

		mutex_unlock(&fd.tree->tree_lock);
		start = hip->cached_start;
		hfsplus_free_extents(sb, hip->cached_extents,
				     alloc_cnt - start, alloc_cnt - blk_cnt);
		hfsplus_dump_extent(hip->cached_extents);
		if (blk_cnt > start) {
			hip->extent_state |= HFSPLUS_EXT_DIRTY;
			break;
		}
		alloc_cnt = start;
		hip->cached_start = hip->cached_blocks = 0;
		hip->extent_state &= ~(HFSPLUS_EXT_DIRTY | HFSPLUS_EXT_NEW);
		mutex_lock(&fd.tree->tree_lock);
	}
	hfs_find_exit(&fd);

	hip->alloc_blocks = blk_cnt;
out_unlock:
	mutex_unlock(&hip->extents_lock);
	hip->phys_size = inode->i_size;
	hip->fs_blocks = (inode->i_size + sb->s_blocksize - 1) >>
		sb->s_blocksize_bits;
	inode_set_bytes(inode, hip->fs_blocks << sb->s_blocksize_bits);
	hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ALLOC_DIRTY);
}