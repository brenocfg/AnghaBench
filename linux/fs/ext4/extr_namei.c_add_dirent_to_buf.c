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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_tail {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_3__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int ext4_find_dest_de (struct inode*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,unsigned int,struct ext4_filename*,struct ext4_dir_entry_2**) ; 
 int ext4_handle_dirty_dirblock (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ext4_has_metadata_csum (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_insert_dentry (struct inode*,struct ext4_dir_entry_2*,unsigned int,struct ext4_filename*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 

__attribute__((used)) static int add_dirent_to_buf(handle_t *handle, struct ext4_filename *fname,
			     struct inode *dir,
			     struct inode *inode, struct ext4_dir_entry_2 *de,
			     struct buffer_head *bh)
{
	unsigned int	blocksize = dir->i_sb->s_blocksize;
	int		csum_size = 0;
	int		err;

	if (ext4_has_metadata_csum(inode->i_sb))
		csum_size = sizeof(struct ext4_dir_entry_tail);

	if (!de) {
		err = ext4_find_dest_de(dir, inode, bh, bh->b_data,
					blocksize - csum_size, fname, &de);
		if (err)
			return err;
	}
	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, bh);
	if (err) {
		ext4_std_error(dir->i_sb, err);
		return err;
	}

	/* By now the buffer is marked for journaling */
	ext4_insert_dentry(inode, de, blocksize, fname);

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
	ext4_mark_inode_dirty(handle, dir);
	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_dirblock(handle, dir, bh);
	if (err)
		ext4_std_error(dir->i_sb, err);
	return 0;
}