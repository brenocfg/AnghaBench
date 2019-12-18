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
typedef  int /*<<< orphan*/  umode_t ;
struct qstr {int /*<<< orphan*/  len; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_dentry_ptr {int dummy; } ;
struct f2fs_dentry_block {int /*<<< orphan*/  dentry_bitmap; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  scalar_t__ f2fs_hash_t ;
struct TYPE_2__ {unsigned int i_current_depth; scalar_t__ chash; unsigned int clevel; int /*<<< orphan*/  i_sem; int /*<<< orphan*/  i_dir_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ENOSPC ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FAULT_DIR_DEPTH ; 
 int /*<<< orphan*/  FI_NEW_INODE ; 
 int GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned int MAX_DIR_HASH_DEPTH ; 
 unsigned int NR_DENTRY_IN_BLOCK ; 
 int PTR_ERR (struct page*) ; 
 unsigned int bucket_blocks (unsigned int) ; 
 unsigned long dir_block_index (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int dir_buckets (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ f2fs_dentry_hash (struct inode*,struct qstr const*,int /*<<< orphan*/ *) ; 
 struct page* f2fs_get_new_data_page (struct inode*,int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  f2fs_i_pino_write (struct inode*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_init_inode_metadata (struct inode*,struct inode*,struct qstr const*,struct qstr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int f2fs_room_for_filename (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_dentry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct f2fs_dentry_ptr*,struct qstr const*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_update_parent_metadata (struct inode*,struct inode*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  make_dentry_ptr_block (int /*<<< orphan*/ *,struct f2fs_dentry_ptr*,struct f2fs_dentry_block*) ; 
 struct f2fs_dentry_block* page_address (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 scalar_t__ time_to_inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_add_regular_entry(struct inode *dir, const struct qstr *new_name,
				const struct qstr *orig_name,
				struct inode *inode, nid_t ino, umode_t mode)
{
	unsigned int bit_pos;
	unsigned int level;
	unsigned int current_depth;
	unsigned long bidx, block;
	f2fs_hash_t dentry_hash;
	unsigned int nbucket, nblock;
	struct page *dentry_page = NULL;
	struct f2fs_dentry_block *dentry_blk = NULL;
	struct f2fs_dentry_ptr d;
	struct page *page = NULL;
	int slots, err = 0;

	level = 0;
	slots = GET_DENTRY_SLOTS(new_name->len);
	dentry_hash = f2fs_dentry_hash(dir, new_name, NULL);

	current_depth = F2FS_I(dir)->i_current_depth;
	if (F2FS_I(dir)->chash == dentry_hash) {
		level = F2FS_I(dir)->clevel;
		F2FS_I(dir)->chash = 0;
	}

start:
	if (time_to_inject(F2FS_I_SB(dir), FAULT_DIR_DEPTH)) {
		f2fs_show_injection_info(FAULT_DIR_DEPTH);
		return -ENOSPC;
	}

	if (unlikely(current_depth == MAX_DIR_HASH_DEPTH))
		return -ENOSPC;

	/* Increase the depth, if required */
	if (level == current_depth)
		++current_depth;

	nbucket = dir_buckets(level, F2FS_I(dir)->i_dir_level);
	nblock = bucket_blocks(level);

	bidx = dir_block_index(level, F2FS_I(dir)->i_dir_level,
				(le32_to_cpu(dentry_hash) % nbucket));

	for (block = bidx; block <= (bidx + nblock - 1); block++) {
		dentry_page = f2fs_get_new_data_page(dir, NULL, block, true);
		if (IS_ERR(dentry_page))
			return PTR_ERR(dentry_page);

		dentry_blk = page_address(dentry_page);
		bit_pos = f2fs_room_for_filename(&dentry_blk->dentry_bitmap,
						slots, NR_DENTRY_IN_BLOCK);
		if (bit_pos < NR_DENTRY_IN_BLOCK)
			goto add_dentry;

		f2fs_put_page(dentry_page, 1);
	}

	/* Move to next level to find the empty slot for new dentry */
	++level;
	goto start;
add_dentry:
	f2fs_wait_on_page_writeback(dentry_page, DATA, true, true);

	if (inode) {
		down_write(&F2FS_I(inode)->i_sem);
		page = f2fs_init_inode_metadata(inode, dir, new_name,
						orig_name, NULL);
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			goto fail;
		}
	}

	make_dentry_ptr_block(NULL, &d, dentry_blk);
	f2fs_update_dentry(ino, mode, &d, new_name, dentry_hash, bit_pos);

	set_page_dirty(dentry_page);

	if (inode) {
		f2fs_i_pino_write(inode, dir->i_ino);

		/* synchronize inode page's data from inode cache */
		if (is_inode_flag_set(inode, FI_NEW_INODE))
			f2fs_update_inode(inode, page);

		f2fs_put_page(page, 1);
	}

	f2fs_update_parent_metadata(dir, inode, current_depth);
fail:
	if (inode)
		up_write(&F2FS_I(inode)->i_sem);

	f2fs_put_page(dentry_page, 1);

	return err;
}