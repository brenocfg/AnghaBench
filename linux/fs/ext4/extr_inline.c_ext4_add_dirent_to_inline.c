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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int ext4_find_dest_de (struct inode*,struct inode*,int /*<<< orphan*/ ,void*,int,struct ext4_filename*,struct ext4_dir_entry_2**) ; 
 int /*<<< orphan*/  ext4_insert_dentry (struct inode*,struct ext4_dir_entry_2*,int,struct ext4_filename*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_show_inline_dir (struct inode*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 

__attribute__((used)) static int ext4_add_dirent_to_inline(handle_t *handle,
				     struct ext4_filename *fname,
				     struct inode *dir,
				     struct inode *inode,
				     struct ext4_iloc *iloc,
				     void *inline_start, int inline_size)
{
	int		err;
	struct ext4_dir_entry_2 *de;

	err = ext4_find_dest_de(dir, inode, iloc->bh, inline_start,
				inline_size, fname, &de);
	if (err)
		return err;

	BUFFER_TRACE(iloc->bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, iloc->bh);
	if (err)
		return err;
	ext4_insert_dentry(inode, de, inline_size, fname);

	ext4_show_inline_dir(dir, iloc->bh, inline_start, inline_size);

	/*
	 * XXX shouldn't update any times until successful
	 * completion of syscall, but too many callers depend
	 * on this.
	 *
	 * XXX similarly, too many callers depend on
	 * ext4_new_inode() setting the times, but error
	 * recovery deletes the inode, so the worst that can
	 * happen is that the times are slightly out of date
	 * and/or different from the directory change time.
	 */
	dir->i_mtime = dir->i_ctime = current_time(dir);
	ext4_update_dx_flag(dir);
	inode_inc_iversion(dir);
	return 1;
}