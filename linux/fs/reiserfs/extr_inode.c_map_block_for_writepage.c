#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_transaction_handle {scalar_t__ t_trans_id; } ;
struct item_head {int dummy; } ;
struct inode {int i_size; int i_ino; TYPE_3__* i_sb; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {int b_size; scalar_t__ b_blocknr; int /*<<< orphan*/  b_page; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_19__ {int s_blocksize_bits; } ;
struct TYPE_18__ {int pos_in_item; } ;

/* Variables and functions */
 int EIO ; 
 int GET_BLOCK_CREATE ; 
 int GET_BLOCK_NO_DANGLE ; 
 int GET_BLOCK_NO_IMUX ; 
 int /*<<< orphan*/  INITIALIZE_PATH (TYPE_1__) ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int PAGE_SIZE ; 
 int POSITION_FOUND ; 
 int /*<<< orphan*/  TYPE_ANY ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  copy_item_head (struct item_head*,struct item_head*) ; 
 scalar_t__ cpu_key_k_offset (struct cpu_key*) ; 
 scalar_t__ fs_changed (int,TYPE_3__*) ; 
 int /*<<< orphan*/  get_block_num (int /*<<< orphan*/ *,int) ; 
 int get_generation (TYPE_3__*) ; 
 struct buffer_head* get_last_bh (TYPE_1__*) ; 
 scalar_t__ ih_item_body (struct buffer_head*,struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ indirect_item_found (int,struct item_head*) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 scalar_t__ item_moved (struct item_head*,TYPE_1__*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,TYPE_3__*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct buffer_head*) ; 
 int /*<<< orphan*/  kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 char* page_address (int /*<<< orphan*/ ) ; 
 TYPE_1__ path ; 
 int /*<<< orphan*/  pathrelse (TYPE_1__*) ; 
 int reiserfs_get_block (struct inode*,unsigned long,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (TYPE_3__*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (TYPE_3__*,struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (TYPE_3__*,char*,char*,int) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_3__*) ; 
 int search_for_position_by_key (TYPE_3__*,struct cpu_key*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_block_dev_mapped (struct buffer_head*,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,scalar_t__) ; 
 int /*<<< orphan*/ * tp_item_body (TYPE_1__*) ; 
 struct item_head* tp_item_head (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int map_block_for_writepage(struct inode *inode,
				   struct buffer_head *bh_result,
				   unsigned long block)
{
	struct reiserfs_transaction_handle th;
	int fs_gen;
	struct item_head tmp_ih;
	struct item_head *ih;
	struct buffer_head *bh;
	__le32 *item;
	struct cpu_key key;
	INITIALIZE_PATH(path);
	int pos_in_item;
	int jbegin_count = JOURNAL_PER_BALANCE_CNT;
	loff_t byte_offset = ((loff_t)block << inode->i_sb->s_blocksize_bits)+1;
	int retval;
	int use_get_block = 0;
	int bytes_copied = 0;
	int copy_size;
	int trans_running = 0;

	/*
	 * catch places below that try to log something without
	 * starting a trans
	 */
	th.t_trans_id = 0;

	if (!buffer_uptodate(bh_result)) {
		return -EIO;
	}

	kmap(bh_result->b_page);
start_over:
	reiserfs_write_lock(inode->i_sb);
	make_cpu_key(&key, inode, byte_offset, TYPE_ANY, 3);

research:
	retval = search_for_position_by_key(inode->i_sb, &key, &path);
	if (retval != POSITION_FOUND) {
		use_get_block = 1;
		goto out;
	}

	bh = get_last_bh(&path);
	ih = tp_item_head(&path);
	item = tp_item_body(&path);
	pos_in_item = path.pos_in_item;

	/* we've found an unformatted node */
	if (indirect_item_found(retval, ih)) {
		if (bytes_copied > 0) {
			reiserfs_warning(inode->i_sb, "clm-6002",
					 "bytes_copied %d", bytes_copied);
		}
		if (!get_block_num(item, pos_in_item)) {
			/* crap, we are writing to a hole */
			use_get_block = 1;
			goto out;
		}
		set_block_dev_mapped(bh_result,
				     get_block_num(item, pos_in_item), inode);
	} else if (is_direct_le_ih(ih)) {
		char *p;
		p = page_address(bh_result->b_page);
		p += (byte_offset - 1) & (PAGE_SIZE - 1);
		copy_size = ih_item_len(ih) - pos_in_item;

		fs_gen = get_generation(inode->i_sb);
		copy_item_head(&tmp_ih, ih);

		if (!trans_running) {
			/* vs-3050 is gone, no need to drop the path */
			retval = journal_begin(&th, inode->i_sb, jbegin_count);
			if (retval)
				goto out;
			reiserfs_update_inode_transaction(inode);
			trans_running = 1;
			if (fs_changed(fs_gen, inode->i_sb)
			    && item_moved(&tmp_ih, &path)) {
				reiserfs_restore_prepared_buffer(inode->i_sb,
								 bh);
				goto research;
			}
		}

		reiserfs_prepare_for_journal(inode->i_sb, bh, 1);

		if (fs_changed(fs_gen, inode->i_sb)
		    && item_moved(&tmp_ih, &path)) {
			reiserfs_restore_prepared_buffer(inode->i_sb, bh);
			goto research;
		}

		memcpy(ih_item_body(bh, ih) + pos_in_item, p + bytes_copied,
		       copy_size);

		journal_mark_dirty(&th, bh);
		bytes_copied += copy_size;
		set_block_dev_mapped(bh_result, 0, inode);

		/* are there still bytes left? */
		if (bytes_copied < bh_result->b_size &&
		    (byte_offset + bytes_copied) < inode->i_size) {
			set_cpu_key_k_offset(&key,
					     cpu_key_k_offset(&key) +
					     copy_size);
			goto research;
		}
	} else {
		reiserfs_warning(inode->i_sb, "clm-6003",
				 "bad item inode %lu", inode->i_ino);
		retval = -EIO;
		goto out;
	}
	retval = 0;

out:
	pathrelse(&path);
	if (trans_running) {
		int err = journal_end(&th);
		if (err)
			retval = err;
		trans_running = 0;
	}
	reiserfs_write_unlock(inode->i_sb);

	/* this is where we fill in holes in the file. */
	if (use_get_block) {
		retval = reiserfs_get_block(inode, block, bh_result,
					    GET_BLOCK_CREATE | GET_BLOCK_NO_IMUX
					    | GET_BLOCK_NO_DANGLE);
		if (!retval) {
			if (!buffer_mapped(bh_result)
			    || bh_result->b_blocknr == 0) {
				/* get_block failed to find a mapped unformatted node. */
				use_get_block = 0;
				goto start_over;
			}
		}
	}
	kunmap(bh_result->b_page);

	if (!retval && buffer_mapped(bh_result) && bh_result->b_blocknr == 0) {
		/*
		 * we've copied data from the page into the direct item, so the
		 * buffer in the page is now clean, mark it to reflect that.
		 */
		lock_buffer(bh_result);
		clear_buffer_dirty(bh_result);
		unlock_buffer(bh_result);
	}
	return retval;
}