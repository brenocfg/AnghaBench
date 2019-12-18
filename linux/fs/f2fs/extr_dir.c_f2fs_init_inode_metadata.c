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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int DUMMY_ENCRYPTION_ENABLED (int /*<<< orphan*/ ) ; 
 struct page* ERR_PTR (int) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_INC_LINK ; 
 int /*<<< orphan*/  FI_NEW_INODE ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 struct page* f2fs_get_node_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_i_links_write (struct inode*,int) ; 
 int f2fs_init_acl (struct inode*,struct inode*,struct page*,struct page*) ; 
 int f2fs_init_security (struct inode*,struct inode*,struct qstr const*,struct page*) ; 
 scalar_t__ f2fs_may_encrypt (struct inode*) ; 
 struct page* f2fs_new_inode_page (struct inode*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_remove_orphan_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 
 int /*<<< orphan*/  file_lost_pino (struct inode*) ; 
 int /*<<< orphan*/  file_set_enc_name (struct inode*) ; 
 int fscrypt_inherit_context (struct inode*,struct inode*,struct page*,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  init_dent_inode (struct qstr const*,struct page*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int make_empty_dir (struct inode*,struct inode*,struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

struct page *f2fs_init_inode_metadata(struct inode *inode, struct inode *dir,
			const struct qstr *new_name, const struct qstr *orig_name,
			struct page *dpage)
{
	struct page *page;
	int dummy_encrypt = DUMMY_ENCRYPTION_ENABLED(F2FS_I_SB(dir));
	int err;

	if (is_inode_flag_set(inode, FI_NEW_INODE)) {
		page = f2fs_new_inode_page(inode);
		if (IS_ERR(page))
			return page;

		if (S_ISDIR(inode->i_mode)) {
			/* in order to handle error case */
			get_page(page);
			err = make_empty_dir(inode, dir, page);
			if (err) {
				lock_page(page);
				goto put_error;
			}
			put_page(page);
		}

		err = f2fs_init_acl(inode, dir, page, dpage);
		if (err)
			goto put_error;

		err = f2fs_init_security(inode, dir, orig_name, page);
		if (err)
			goto put_error;

		if ((IS_ENCRYPTED(dir) || dummy_encrypt) &&
					f2fs_may_encrypt(inode)) {
			err = fscrypt_inherit_context(dir, inode, page, false);
			if (err)
				goto put_error;
		}
	} else {
		page = f2fs_get_node_page(F2FS_I_SB(dir), inode->i_ino);
		if (IS_ERR(page))
			return page;
	}

	if (new_name) {
		init_dent_inode(new_name, page);
		if (IS_ENCRYPTED(dir))
			file_set_enc_name(inode);
	}

	/*
	 * This file should be checkpointed during fsync.
	 * We lost i_pino from now on.
	 */
	if (is_inode_flag_set(inode, FI_INC_LINK)) {
		if (!S_ISDIR(inode->i_mode))
			file_lost_pino(inode);
		/*
		 * If link the tmpfile to alias through linkat path,
		 * we should remove this inode from orphan list.
		 */
		if (inode->i_nlink == 0)
			f2fs_remove_orphan_inode(F2FS_I_SB(dir), inode->i_ino);
		f2fs_i_links_write(inode, true);
	}
	return page;

put_error:
	clear_nlink(inode);
	f2fs_update_inode(inode, page);
	f2fs_put_page(page, 1);
	return ERR_PTR(err);
}