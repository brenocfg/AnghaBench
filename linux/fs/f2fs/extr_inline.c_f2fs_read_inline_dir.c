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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct fscrypt_str {int dummy; } ;
struct file {int dummy; } ;
struct f2fs_dentry_ptr {scalar_t__ max; } ;
struct dir_context {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int f2fs_fill_dentries (struct dir_context*,struct f2fs_dentry_ptr*,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 struct page* f2fs_get_node_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  make_dentry_ptr_inline (struct inode*,struct f2fs_dentry_ptr*,void*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int f2fs_read_inline_dir(struct file *file, struct dir_context *ctx,
				struct fscrypt_str *fstr)
{
	struct inode *inode = file_inode(file);
	struct page *ipage = NULL;
	struct f2fs_dentry_ptr d;
	void *inline_dentry = NULL;
	int err;

	make_dentry_ptr_inline(inode, &d, inline_dentry);

	if (ctx->pos == d.max)
		return 0;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	if (IS_ERR(ipage))
		return PTR_ERR(ipage);

	/*
	 * f2fs_readdir was protected by inode.i_rwsem, it is safe to access
	 * ipage without page's lock held.
	 */
	unlock_page(ipage);

	inline_dentry = inline_data_addr(inode, ipage);

	make_dentry_ptr_inline(inode, &d, inline_dentry);

	err = f2fs_fill_dentries(ctx, &d, 0, fstr);
	if (!err)
		ctx->pos = d.max;

	f2fs_put_page(ipage, 0);
	return err < 0 ? err : 0;
}