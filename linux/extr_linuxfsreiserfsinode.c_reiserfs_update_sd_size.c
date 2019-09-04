#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct item_head {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 int IO_ERROR ; 
 int ITEM_NOT_FOUND ; 
 int PATH_LAST_POSITION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SD_OFFSET ; 
 int /*<<< orphan*/  TYPE_STAT_DATA ; 
 int /*<<< orphan*/  copy_item_head (struct item_head*,struct item_head*) ; 
 scalar_t__ fs_changed (int,int /*<<< orphan*/ ) ; 
 int get_generation (int /*<<< orphan*/ ) ; 
 struct buffer_head* get_last_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ item_moved (struct item_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct buffer_head*) ; 
 int /*<<< orphan*/  make_cpu_key (struct cpu_key*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_check_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_error (int /*<<< orphan*/ ,char*,char*,struct cpu_key*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int search_item (int /*<<< orphan*/ ,struct cpu_key*,int /*<<< orphan*/ *) ; 
 struct item_head* tp_item_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_stat_data (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 

void reiserfs_update_sd_size(struct reiserfs_transaction_handle *th,
			     struct inode *inode, loff_t size)
{
	struct cpu_key key;
	INITIALIZE_PATH(path);
	struct buffer_head *bh;
	int fs_gen;
	struct item_head *ih, tmp_ih;
	int retval;

	BUG_ON(!th->t_trans_id);

	/* key type is unimportant */
	make_cpu_key(&key, inode, SD_OFFSET, TYPE_STAT_DATA, 3);

	for (;;) {
		int pos;
		/* look for the object's stat data */
		retval = search_item(inode->i_sb, &key, &path);
		if (retval == IO_ERROR) {
			reiserfs_error(inode->i_sb, "vs-13050",
				       "i/o failure occurred trying to "
				       "update %K stat data", &key);
			return;
		}
		if (retval == ITEM_NOT_FOUND) {
			pos = PATH_LAST_POSITION(&path);
			pathrelse(&path);
			if (inode->i_nlink == 0) {
				/*reiserfs_warning (inode->i_sb, "vs-13050: reiserfs_update_sd: i_nlink == 0, stat data not found"); */
				return;
			}
			reiserfs_warning(inode->i_sb, "vs-13060",
					 "stat data of object %k (nlink == %d) "
					 "not found (pos %d)",
					 INODE_PKEY(inode), inode->i_nlink,
					 pos);
			reiserfs_check_path(&path);
			return;
		}

		/*
		 * sigh, prepare_for_journal might schedule.  When it
		 * schedules the FS might change.  We have to detect that,
		 * and loop back to the search if the stat data item has moved
		 */
		bh = get_last_bh(&path);
		ih = tp_item_head(&path);
		copy_item_head(&tmp_ih, ih);
		fs_gen = get_generation(inode->i_sb);
		reiserfs_prepare_for_journal(inode->i_sb, bh, 1);

		/* Stat_data item has been moved after scheduling. */
		if (fs_changed(fs_gen, inode->i_sb)
		    && item_moved(&tmp_ih, &path)) {
			reiserfs_restore_prepared_buffer(inode->i_sb, bh);
			continue;
		}
		break;
	}
	update_stat_data(&path, inode, size);
	journal_mark_dirty(th, bh);
	pathrelse(&path);
	return;
}