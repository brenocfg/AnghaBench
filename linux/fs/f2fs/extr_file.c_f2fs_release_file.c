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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_writecount; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FI_DROP_CACHE ; 
 int /*<<< orphan*/  FI_VOLATILE_FILE ; 
 int FMODE_WRITE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_drop_inmem_pages (struct inode*) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_volatile_file (struct inode*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_dec_volatile_write (struct inode*) ; 

__attribute__((used)) static int f2fs_release_file(struct inode *inode, struct file *filp)
{
	/*
	 * f2fs_relase_file is called at every close calls. So we should
	 * not drop any inmemory pages by close called by other process.
	 */
	if (!(filp->f_mode & FMODE_WRITE) ||
			atomic_read(&inode->i_writecount) != 1)
		return 0;

	/* some remained atomic pages should discarded */
	if (f2fs_is_atomic_file(inode))
		f2fs_drop_inmem_pages(inode);
	if (f2fs_is_volatile_file(inode)) {
		set_inode_flag(inode, FI_DROP_CACHE);
		filemap_fdatawrite(inode->i_mapping);
		clear_inode_flag(inode, FI_DROP_CACHE);
		clear_inode_flag(inode, FI_VOLATILE_FILE);
		stat_dec_volatile_write(inode);
	}
	return 0;
}