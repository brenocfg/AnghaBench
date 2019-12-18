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
struct inode {TYPE_1__* i_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_len; int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_GET_BLOCKS_PRE_IO ; 
 unsigned long EXT_UNWRITTEN_MAX_LEN ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int ext4_ext_convert_to_initialized (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path**,scalar_t__,unsigned long,int) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_find_goal (struct inode*,struct ext4_ext_path*,scalar_t__) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_insert_extent (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path**,struct ext4_extent*,int) ; 
 scalar_t__ ext4_ext_is_unwritten (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_mark_unwritten (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_next_allocated_block (struct ext4_ext_path*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_show_leaf (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,scalar_t__) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_blocks (void*,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (void*,int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_new_meta_blocks (void*,int /*<<< orphan*/ *,struct inode*,int,int /*<<< orphan*/ ,unsigned long*,int*) ; 
 int ext_depth (struct inode*) ; 
 int /*<<< orphan*/  get_default_free_blocks_flags (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

int ext4_ext_get_blocks(void *icb, handle_t *handle, struct inode *inode, ext4_fsblk_t iblock,
		unsigned long max_blocks, struct buffer_head *bh_result,
		int create, int flags)
{
	struct ext4_ext_path *path = NULL;
	struct ext4_extent newex, *ex;
	int goal, err = 0, depth;
	unsigned long allocated = 0;
	ext4_fsblk_t next, newblock;

	clear_buffer_new(bh_result);
	/*mutex_lock(&ext4_I(inode)->truncate_mutex);*/

	/* find extent for this block */
	path = ext4_find_extent(inode, iblock, NULL, 0);
	if (IS_ERR(path)) {
		err = PTR_ERR(path);
		path = NULL;
		goto out2;
	}

	depth = ext_depth(inode);

	/*
	 * consistent leaf must not be empty
	 * this situations is possible, though, _during_ tree modification
	 * this is why assert can't be put in ext4_ext_find_extent()
	 */
	BUG_ON(path[depth].p_ext == NULL && depth != 0);

	if ((ex = path[depth].p_ext)) {
		ext4_lblk_t ee_block = le32_to_cpu(ex->ee_block);
		ext4_fsblk_t ee_start = ext4_ext_pblock(ex);
		unsigned short ee_len  = ext4_ext_get_actual_len(ex);
		/* if found exent covers block, simple return it */
		if (iblock >= ee_block && iblock < ee_block + ee_len) {

			/* number of remain blocks in the extent */
			allocated = ee_len + ee_block - iblock;

			if (ext4_ext_is_unwritten(ex)) {
				if (create) {
					newblock = iblock - ee_block + ee_start;
					err = ext4_ext_convert_to_initialized (
							icb, handle,
							inode,
							&path,
							iblock,
							allocated,
							flags);
					if (err)
						goto out2;

				} else {
					newblock = 0;
				}
			} else {
				newblock = iblock - ee_block + ee_start;
			}
			goto out;
		}
	}

	/*
	 * requested block isn't allocated yet
	 * we couldn't try to create block if create flag is zero
	 */
	if (!create) {
		goto out2;
	}

	/* find next allocated block so that we know how many
	 * blocks we can allocate without ovelapping next extent */
	next = ext4_ext_next_allocated_block(path);
	BUG_ON(next <= iblock);
	allocated = next - iblock;
	if (flags & EXT4_GET_BLOCKS_PRE_IO && max_blocks > EXT_UNWRITTEN_MAX_LEN)
		max_blocks = EXT_UNWRITTEN_MAX_LEN;
	if (allocated > max_blocks)
		allocated = max_blocks;

	/* allocate new block */
	goal = ext4_ext_find_goal(inode, path, iblock);

	newblock = ext4_new_meta_blocks(icb, handle, inode, goal, 0,
			&allocated, &err);
	if (!newblock)
		goto out2;

	/* try to insert new extent into found leaf and return */
	newex.ee_block = cpu_to_le32(iblock);
	ext4_ext_store_pblock(&newex, newblock);
	newex.ee_len = cpu_to_le16(allocated);
	/* if it's fallocate, mark ex as unwritten */
	if (flags & EXT4_GET_BLOCKS_PRE_IO) {
		ext4_ext_mark_unwritten(&newex);
	}
	err = ext4_ext_insert_extent(icb, handle, inode, &path, &newex,
                                 flags & EXT4_GET_BLOCKS_PRE_IO);

	if (err) {
		/* free data blocks we just allocated */
		ext4_free_blocks(icb, handle, inode, NULL, ext4_ext_pblock(&newex),
				le16_to_cpu(newex.ee_len), get_default_free_blocks_flags(inode));
		goto out2;
	}
	
	ext4_mark_inode_dirty(icb, handle, inode);

	/* previous routine could use block we allocated */
	if (ext4_ext_is_unwritten(&newex))
		newblock = 0;
	else
		newblock = ext4_ext_pblock(&newex);

	set_buffer_new(bh_result);

out:
	if (allocated > max_blocks)
		allocated = max_blocks;

	ext4_ext_show_leaf(inode, path);
	set_buffer_mapped(bh_result);
	bh_result->b_bdev = inode->i_sb->s_bdev;
	bh_result->b_blocknr = newblock;
out2:
	if (path) {
		ext4_ext_drop_refs(path);
		kfree(path);
	}
	/*mutex_unlock(&ext4_I(inode)->truncate_mutex);*/

	return err ? err : allocated;
}