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
struct TYPE_2__ {scalar_t__ len; } ;
struct page {unsigned int i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
struct inode {unsigned int i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  ino; } ;
struct dentry {unsigned int i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; TYPE_1__ d_name; } ;
typedef  int nid_t ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int EPERM ; 
 struct page* ERR_PTR (int) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct page*) ; 
 scalar_t__ F2FS_NAME_LEN ; 
 unsigned int F2FS_ROOT_INO (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int __recover_dot_dentries (struct page*,unsigned int) ; 
 struct page* d_splice_alias (struct page*,struct page*) ; 
 scalar_t__ f2fs_encrypted_inode (struct page*) ; 
 struct f2fs_dir_entry* f2fs_find_entry (struct page*,TYPE_1__*,struct page**) ; 
 scalar_t__ f2fs_has_inline_dots (struct page*) ; 
 struct page* f2fs_iget (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct page*,struct page*) ; 
 int fscrypt_prepare_lookup (struct page*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  iput (struct page*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_end (struct page*,struct page*,int,int) ; 
 int /*<<< orphan*/  trace_f2fs_lookup_start (struct page*,struct page*,unsigned int) ; 

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

	trace_f2fs_lookup_start(dir, dentry, flags);

	err = fscrypt_prepare_lookup(dir, dentry, flags);
	if (err)
		goto out;

	if (dentry->d_name.len > F2FS_NAME_LEN) {
		err = -ENAMETOOLONG;
		goto out;
	}

	de = f2fs_find_entry(dir, &dentry->d_name, &page);
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
	if (f2fs_encrypted_inode(dir) &&
	    (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
	    !fscrypt_has_permitted_context(dir, inode)) {
		f2fs_msg(inode->i_sb, KERN_WARNING,
			 "Inconsistent encryption contexts: %lu/%lu",
			 dir->i_ino, inode->i_ino);
		err = -EPERM;
		goto out_iput;
	}
out_splice:
	new = d_splice_alias(inode, dentry);
	if (IS_ERR(new))
		err = PTR_ERR(new);
	trace_f2fs_lookup_end(dir, dentry, ino, err);
	return new;
out_iput:
	iput(inode);
out:
	trace_f2fs_lookup_end(dir, dentry, ino, err);
	return ERR_PTR(err);
}