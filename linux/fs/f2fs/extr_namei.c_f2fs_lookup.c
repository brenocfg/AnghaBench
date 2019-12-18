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
struct page {unsigned int i_ino; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct inode {unsigned int i_ino; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct fscrypt_name {int dummy; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  ino; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int nid_t ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int EPERM ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct page*) ; 
 scalar_t__ F2FS_NAME_LEN ; 
 unsigned int F2FS_ROOT_INO (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CASEFOLDED (struct page*) ; 
 scalar_t__ IS_ENCRYPTED (struct page*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int PTR_ERR_OR_ZERO (struct dentry*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct f2fs_dir_entry* __f2fs_find_entry (struct page*,struct fscrypt_name*,struct page**) ; 
 int __recover_dot_dentries (struct page*,unsigned int) ; 
 struct dentry* d_splice_alias (struct page*,struct dentry*) ; 
 scalar_t__ f2fs_has_inline_dots (struct page*) ; 
 struct page* f2fs_iget (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_warn (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct page*,struct page*) ; 
 int fscrypt_prepare_lookup (struct page*,struct dentry*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  iput (struct page*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_end (struct page*,struct dentry*,int,int) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_start (struct page*,struct dentry*,unsigned int) ; 

__attribute__((used)) static struct dentry *f2fs_lookup(struct inode *dir, struct dentry *dentry,
		unsigned int flags)
{
	struct inode *inode = NULL;
	struct f2fs_dir_entry *de;
	struct page *page;
	struct dentry *new;
	nid_t ino = -1;
	int err = 0;
	unsigned int root_ino = F2FS_ROOT_INO(F2FS_I_SB(dir));
	struct fscrypt_name fname;

	trace_f2fs_lookup_start(dir, dentry, flags);

	if (dentry->d_name.len > F2FS_NAME_LEN) {
		err = -ENAMETOOLONG;
		goto out;
	}

	err = fscrypt_prepare_lookup(dir, dentry, &fname);
	if (err == -ENOENT)
		goto out_splice;
	if (err)
		goto out;
	de = __f2fs_find_entry(dir, &fname, &page);
	fscrypt_free_filename(&fname);

	if (!de) {
		if (IS_ERR(page)) {
			err = PTR_ERR(page);
			goto out;
		}
		goto out_splice;
	}

	ino = le32_to_cpu(de->ino);
	f2fs_put_page(page, 0);

	inode = f2fs_iget(dir->i_sb, ino);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out;
	}

	if ((dir->i_ino == root_ino) && f2fs_has_inline_dots(dir)) {
		err = __recover_dot_dentries(dir, root_ino);
		if (err)
			goto out_iput;
	}

	if (f2fs_has_inline_dots(inode)) {
		err = __recover_dot_dentries(inode, dir->i_ino);
		if (err)
			goto out_iput;
	}
	if (IS_ENCRYPTED(dir) &&
	    (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
	    !fscrypt_has_permitted_context(dir, inode)) {
		f2fs_warn(F2FS_I_SB(inode), "Inconsistent encryption contexts: %lu/%lu",
			  dir->i_ino, inode->i_ino);
		err = -EPERM;
		goto out_iput;
	}
out_splice:
#ifdef CONFIG_UNICODE
	if (!inode && IS_CASEFOLDED(dir)) {
		/* Eventually we want to call d_add_ci(dentry, NULL)
		 * for negative dentries in the encoding case as
		 * well.  For now, prevent the negative dentry
		 * from being cached.
		 */
		trace_f2fs_lookup_end(dir, dentry, ino, err);
		return NULL;
	}
#endif
	new = d_splice_alias(inode, dentry);
	err = PTR_ERR_OR_ZERO(new);
	trace_f2fs_lookup_end(dir, dentry, ino, err);
	return new;
out_iput:
	iput(inode);
out:
	trace_f2fs_lookup_end(dir, dentry, ino, err);
	return ERR_PTR(err);
}