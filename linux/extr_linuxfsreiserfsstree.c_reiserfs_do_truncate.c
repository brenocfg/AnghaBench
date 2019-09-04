#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct page {int dummy; } ;
struct item_head {int dummy; } ;
struct inode {int i_size; void* i_ctime; void* i_mtime; TYPE_3__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_13__ {struct cpu_key* k_objectid; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;
typedef  int loff_t ;
struct TYPE_15__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_14__ {int reada; int /*<<< orphan*/  pos_in_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int FILE_NOT_FOUND ; 
 int /*<<< orphan*/  INITIALIZE_PATH (TYPE_2__) ; 
 int IO_ERROR ; 
 scalar_t__ JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int PATH_READA ; 
 int PATH_READA_BACK ; 
 int POSITION_FOUND ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,int,struct cpu_key*) ; 
 int ROUND_UP (int) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DIRECT ; 
 void* current_time (struct inode*) ; 
 scalar_t__ is_statdata_le_ih (struct item_head*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,TYPE_3__*,scalar_t__) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 scalar_t__ journal_transaction_should_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_reiserfs_offset (struct inode*) ; 
 int op_bytes_number (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathrelse (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_check_path (TYPE_2__*) ; 
 int reiserfs_cut_from_item (struct reiserfs_transaction_handle*,TYPE_2__*,struct cpu_key*,struct inode*,struct page*,int) ; 
 int /*<<< orphan*/  reiserfs_error (TYPE_3__*,char*,char*,...) ; 
 scalar_t__ reiserfs_transaction_free_space (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (TYPE_3__*,char*,char*) ; 
 TYPE_2__ s_search_path ; 
 int search_for_position_by_key (TYPE_3__*,struct cpu_key*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_cpu_key_k_offset (struct cpu_key*,int) ; 
 struct item_head* tp_item_head (TYPE_2__*) ; 
 int /*<<< orphan*/  truncate_directory (struct reiserfs_transaction_handle*,struct inode*) ; 

int reiserfs_do_truncate(struct reiserfs_transaction_handle *th,
			 struct inode *inode,	/* ->i_size contains new size */
			 struct page *page,	/* up to date for last block */
			 /*
			  * when it is called by file_release to convert
			  * the tail - no timestamps should be updated
			  */
			 int update_timestamps
    )
{
	INITIALIZE_PATH(s_search_path);	/* Path to the current object item. */
	struct item_head *p_le_ih;	/* Pointer to an item header. */

	/* Key to search for a previous file item. */
	struct cpu_key s_item_key;
	loff_t file_size,	/* Old file size. */
	 new_file_size;	/* New file size. */
	int deleted;		/* Number of deleted or truncated bytes. */
	int retval;
	int err = 0;

	BUG_ON(!th->t_trans_id);
	if (!
	    (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode)
	     || S_ISLNK(inode->i_mode)))
		return 0;

	/* deletion of directory - no need to update timestamps */
	if (S_ISDIR(inode->i_mode)) {
		truncate_directory(th, inode);
		return 0;
	}

	/* Get new file size. */
	new_file_size = inode->i_size;

	/* FIXME: note, that key type is unimportant here */
	make_cpu_key(&s_item_key, inode, max_reiserfs_offset(inode),
		     TYPE_DIRECT, 3);

	retval =
	    search_for_position_by_key(inode->i_sb, &s_item_key,
				       &s_search_path);
	if (retval == IO_ERROR) {
		reiserfs_error(inode->i_sb, "vs-5657",
			       "i/o failure occurred trying to truncate %K",
			       &s_item_key);
		err = -EIO;
		goto out;
	}
	if (retval == POSITION_FOUND || retval == FILE_NOT_FOUND) {
		reiserfs_error(inode->i_sb, "PAP-5660",
			       "wrong result %d of search for %K", retval,
			       &s_item_key);

		err = -EIO;
		goto out;
	}

	s_search_path.pos_in_item--;

	/* Get real file size (total length of all file items) */
	p_le_ih = tp_item_head(&s_search_path);
	if (is_statdata_le_ih(p_le_ih))
		file_size = 0;
	else {
		loff_t offset = le_ih_k_offset(p_le_ih);
		int bytes =
		    op_bytes_number(p_le_ih, inode->i_sb->s_blocksize);

		/*
		 * this may mismatch with real file size: if last direct item
		 * had no padding zeros and last unformatted node had no free
		 * space, this file would have this file size
		 */
		file_size = offset + bytes - 1;
	}
	/*
	 * are we doing a full truncate or delete, if so
	 * kick in the reada code
	 */
	if (new_file_size == 0)
		s_search_path.reada = PATH_READA | PATH_READA_BACK;

	if (file_size == 0 || file_size < new_file_size) {
		goto update_and_out;
	}

	/* Update key to search for the last file item. */
	set_cpu_key_k_offset(&s_item_key, file_size);

	do {
		/* Cut or delete file item. */
		deleted =
		    reiserfs_cut_from_item(th, &s_search_path, &s_item_key,
					   inode, page, new_file_size);
		if (deleted < 0) {
			reiserfs_warning(inode->i_sb, "vs-5665",
					 "reiserfs_cut_from_item failed");
			reiserfs_check_path(&s_search_path);
			return 0;
		}

		RFALSE(deleted > file_size,
		       "PAP-5670: reiserfs_cut_from_item: too many bytes deleted: deleted %d, file_size %lu, item_key %K",
		       deleted, file_size, &s_item_key);

		/* Change key to search the last file item. */
		file_size -= deleted;

		set_cpu_key_k_offset(&s_item_key, file_size);

		/*
		 * While there are bytes to truncate and previous
		 * file item is presented in the tree.
		 */

		/*
		 * This loop could take a really long time, and could log
		 * many more blocks than a transaction can hold.  So, we do
		 * a polite journal end here, and if the transaction needs
		 * ending, we make sure the file is consistent before ending
		 * the current trans and starting a new one
		 */
		if (journal_transaction_should_end(th, 0) ||
		    reiserfs_transaction_free_space(th) <= JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD) {
			pathrelse(&s_search_path);

			if (update_timestamps) {
				inode->i_mtime = current_time(inode);
				inode->i_ctime = current_time(inode);
			}
			reiserfs_update_sd(th, inode);

			err = journal_end(th);
			if (err)
				goto out;
			err = journal_begin(th, inode->i_sb,
					    JOURNAL_FOR_FREE_BLOCK_AND_UPDATE_SD + JOURNAL_PER_BALANCE_CNT * 4) ;
			if (err)
				goto out;
			reiserfs_update_inode_transaction(inode);
		}
	} while (file_size > ROUND_UP(new_file_size) &&
		 search_for_position_by_key(inode->i_sb, &s_item_key,
					    &s_search_path) == POSITION_FOUND);

	RFALSE(file_size > ROUND_UP(new_file_size),
	       "PAP-5680: truncate did not finish: new_file_size %lld, current %lld, oid %d",
	       new_file_size, file_size, s_item_key.on_disk_key.k_objectid);

update_and_out:
	if (update_timestamps) {
		/* this is truncate, not file closing */
		inode->i_mtime = current_time(inode);
		inode->i_ctime = current_time(inode);
	}
	reiserfs_update_sd(th, inode);

out:
	pathrelse(&s_search_path);
	return err;
}