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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_dentry_ptr {unsigned int max; int /*<<< orphan*/  bitmap; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  int /*<<< orphan*/  f2fs_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NEW_INODE ; 
 int GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int f2fs_convert_inline_dir (struct inode*,struct page*,void*) ; 
 int /*<<< orphan*/  f2fs_dentry_hash (struct inode*,struct qstr const*,int /*<<< orphan*/ *) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_i_pino_write (struct inode*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_init_inode_metadata (struct inode*,struct inode*,struct qstr const*,struct qstr const*,struct page*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 unsigned int f2fs_room_for_filename (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  f2fs_update_dentry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct f2fs_dentry_ptr*,struct qstr const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_update_parent_metadata (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dentry_ptr_inline (struct inode*,struct f2fs_dentry_ptr*,void*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_add_inline_entry(struct inode *dir, const struct qstr *new_name,
				const struct qstr *orig_name,
				struct inode *inode, nid_t ino, umode_t mode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);
	struct page *ipage;
	unsigned int bit_pos;
	f2fs_hash_t name_hash;
	void *inline_dentry = NULL;
	struct f2fs_dentry_ptr d;
	int slots = GET_DENTRY_SLOTS(new_name->len);
	struct page *page = NULL;
	int err = 0;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	if (IS_ERR(ipage))
		return PTR_ERR(ipage);

	inline_dentry = inline_data_addr(dir, ipage);
	make_dentry_ptr_inline(dir, &d, inline_dentry);

	bit_pos = f2fs_room_for_filename(d.bitmap, slots, d.max);
	if (bit_pos >= d.max) {
		err = f2fs_convert_inline_dir(dir, ipage, inline_dentry);
		if (err)
			return err;
		err = -EAGAIN;
		goto out;
	}

	if (inode) {
		down_write(&F2FS_I(inode)->i_sem);
		page = f2fs_init_inode_metadata(inode, dir, new_name,
						orig_name, ipage);
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			goto fail;
		}
	}

	f2fs_wait_on_page_writeback(ipage, NODE, true, true);

	name_hash = f2fs_dentry_hash(dir, new_name, NULL);
	f2fs_update_dentry(ino, mode, &d, new_name, name_hash, bit_pos);

	set_page_dirty(ipage);

	/* we don't need to mark_inode_dirty now */
	if (inode) {
		f2fs_i_pino_write(inode, dir->i_ino);

		/* synchronize inode page's data from inode cache */
		if (is_inode_flag_set(inode, FI_NEW_INODE))
			f2fs_update_inode(inode, page);

		f2fs_put_page(page, 1);
	}

	f2fs_update_parent_metadata(dir, inode, 0);
fail:
	if (inode)
		up_write(&F2FS_I(inode)->i_sem);
out:
	f2fs_put_page(ipage, 1);
	return err;
}