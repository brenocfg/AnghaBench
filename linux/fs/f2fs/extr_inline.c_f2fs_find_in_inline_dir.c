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
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct fscrypt_name {int /*<<< orphan*/  disk_name; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_dir_entry {int dummy; } ;
struct f2fs_dentry_ptr {int dummy; } ;
typedef  int /*<<< orphan*/  f2fs_hash_t ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_SB (int /*<<< orphan*/ ) ; 
 struct qstr FSTR_TO_QSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  f2fs_dentry_hash (struct inode*,struct qstr*,struct fscrypt_name*) ; 
 struct f2fs_dir_entry* f2fs_find_target_dentry (struct fscrypt_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct f2fs_dentry_ptr*) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  make_dentry_ptr_inline (struct inode*,struct f2fs_dentry_ptr*,void*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct f2fs_dir_entry *f2fs_find_in_inline_dir(struct inode *dir,
			struct fscrypt_name *fname, struct page **res_page)
{
	struct f2fs_sb_info *sbi = F2FS_SB(dir->i_sb);
	struct qstr name = FSTR_TO_QSTR(&fname->disk_name);
	struct f2fs_dir_entry *de;
	struct f2fs_dentry_ptr d;
	struct page *ipage;
	void *inline_dentry;
	f2fs_hash_t namehash;

	ipage = f2fs_get_node_page(sbi, dir->i_ino);
	if (IS_ERR(ipage)) {
		*res_page = ipage;
		return NULL;
	}

	namehash = f2fs_dentry_hash(dir, &name, fname);

	inline_dentry = inline_data_addr(dir, ipage);

	make_dentry_ptr_inline(dir, &d, inline_dentry);
	de = f2fs_find_target_dentry(fname, namehash, NULL, &d);
	unlock_page(ipage);
	if (de)
		*res_page = ipage;
	else
		f2fs_put_page(ipage, 0);

	return de;
}