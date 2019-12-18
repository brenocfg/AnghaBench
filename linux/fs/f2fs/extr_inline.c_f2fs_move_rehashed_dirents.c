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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_inline_xattr_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_INLINE_DENTRY ; 
 int /*<<< orphan*/  GFP_F2FS_ZERO ; 
 int /*<<< orphan*/  MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int f2fs_add_inline_entries (struct inode*,void*) ; 
 int /*<<< orphan*/  f2fs_has_inline_xattr (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_depth_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 void* f2fs_kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_sb_has_flexible_inline_xattr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_truncate_inline_inode (struct inode*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  stat_dec_inline_dir (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int f2fs_move_rehashed_dirents(struct inode *dir, struct page *ipage,
							void *inline_dentry)
{
	void *backup_dentry;
	int err;

	backup_dentry = f2fs_kmalloc(F2FS_I_SB(dir),
				MAX_INLINE_DATA(dir), GFP_F2FS_ZERO);
	if (!backup_dentry) {
		f2fs_put_page(ipage, 1);
		return -ENOMEM;
	}

	memcpy(backup_dentry, inline_dentry, MAX_INLINE_DATA(dir));
	f2fs_truncate_inline_inode(dir, ipage, 0);

	unlock_page(ipage);

	err = f2fs_add_inline_entries(dir, backup_dentry);
	if (err)
		goto recover;

	lock_page(ipage);

	stat_dec_inline_dir(dir);
	clear_inode_flag(dir, FI_INLINE_DENTRY);

	/*
	 * should retrieve reserved space which was used to keep
	 * inline_dentry's structure for backward compatibility.
	 */
	if (!f2fs_sb_has_flexible_inline_xattr(F2FS_I_SB(dir)) &&
			!f2fs_has_inline_xattr(dir))
		F2FS_I(dir)->i_inline_xattr_size = 0;

	kvfree(backup_dentry);
	return 0;
recover:
	lock_page(ipage);
	f2fs_wait_on_page_writeback(ipage, NODE, true, true);
	memcpy(inline_dentry, backup_dentry, MAX_INLINE_DATA(dir));
	f2fs_i_depth_write(dir, 0);
	f2fs_i_size_write(dir, MAX_INLINE_DATA(dir));
	set_page_dirty(ipage);
	f2fs_put_page(ipage, 1);

	kvfree(backup_dentry);
	return err;
}