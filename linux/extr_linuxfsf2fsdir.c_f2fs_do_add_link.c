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
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct fscrypt_name {int dummy; } ;
struct f2fs_dir_entry {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_2__ {int /*<<< orphan*/ * task; } ;

/* Variables and functions */
 int EEXIST ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 struct f2fs_dir_entry* __f2fs_find_entry (struct inode*,struct fscrypt_name*,struct page**) ; 
 int /*<<< orphan*/ * current ; 
 int f2fs_add_dentry (struct inode*,struct fscrypt_name*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,struct qstr const*,int /*<<< orphan*/ ,struct fscrypt_name*) ; 

int f2fs_do_add_link(struct inode *dir, const struct qstr *name,
				struct inode *inode, nid_t ino, umode_t mode)
{
	struct fscrypt_name fname;
	struct page *page = NULL;
	struct f2fs_dir_entry *de = NULL;
	int err;

	err = fscrypt_setup_filename(dir, name, 0, &fname);
	if (err)
		return err;

	/*
	 * An immature stakable filesystem shows a race condition between lookup
	 * and create. If we have same task when doing lookup and create, it's
	 * definitely fine as expected by VFS normally. Otherwise, let's just
	 * verify on-disk dentry one more time, which guarantees filesystem
	 * consistency more.
	 */
	if (current != F2FS_I(dir)->task) {
		de = __f2fs_find_entry(dir, &fname, &page);
		F2FS_I(dir)->task = NULL;
	}
	if (de) {
		f2fs_put_page(page, 0);
		err = -EEXIST;
	} else if (IS_ERR(page)) {
		err = PTR_ERR(page);
	} else {
		err = f2fs_add_dentry(dir, &fname, inode, ino, mode);
	}
	fscrypt_free_filename(&fname);
	return err;
}