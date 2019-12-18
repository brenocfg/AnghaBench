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
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct btrfs_inode {scalar_t__ last_unlink_trans; scalar_t__ logged_trans; int /*<<< orphan*/  log_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void btrfs_record_unlink_dir(struct btrfs_trans_handle *trans,
			     struct btrfs_inode *dir, struct btrfs_inode *inode,
			     int for_rename)
{
	/*
	 * when we're logging a file, if it hasn't been renamed
	 * or unlinked, and its inode is fully committed on disk,
	 * we don't have to worry about walking up the directory chain
	 * to log its parents.
	 *
	 * So, we use the last_unlink_trans field to put this transid
	 * into the file.  When the file is logged we check it and
	 * don't log the parents if the file is fully on disk.
	 */
	mutex_lock(&inode->log_mutex);
	inode->last_unlink_trans = trans->transid;
	mutex_unlock(&inode->log_mutex);

	/*
	 * if this directory was already logged any new
	 * names for this file/dir will get recorded
	 */
	if (dir->logged_trans == trans->transid)
		return;

	/*
	 * if the inode we're about to unlink was logged,
	 * the log will be properly updated for any new names
	 */
	if (inode->logged_trans == trans->transid)
		return;

	/*
	 * when renaming files across directories, if the directory
	 * there we're unlinking from gets fsync'd later on, there's
	 * no way to find the destination directory later and fsync it
	 * properly.  So, we have to be conservative and force commits
	 * so the new name gets discovered.
	 */
	if (for_rename)
		goto record;

	/* we can safely do the unlink without any special recording */
	return;

record:
	mutex_lock(&dir->log_mutex);
	dir->last_unlink_trans = trans->transid;
	mutex_unlock(&dir->log_mutex);
}