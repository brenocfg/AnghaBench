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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  inum; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct fscrypt_name {int /*<<< orphan*/  minor_hash; scalar_t__ hash; } ;
struct dentry {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPERM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBIFS_MAX_DENT_NODE_SZ ; 
 scalar_t__ UBIFS_MAX_NLEN ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 scalar_t__ dbg_check_name (struct ubifs_info*,struct ubifs_dent_node*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  dent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,struct fscrypt_name*) ; 
 int /*<<< orphan*/  dent_key_init_hash (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fname_len (struct fscrypt_name*) ; 
 int /*<<< orphan*/ * fname_name (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,struct inode*) ; 
 int fscrypt_prepare_lookup (struct inode*,struct inode*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_crypt_is_encrypted (struct inode*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,struct inode*,int) ; 
 struct inode* ubifs_iget (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_lookup_dh (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,int /*<<< orphan*/ ) ; 
 int ubifs_tnc_lookup_nm (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  ubifs_warn (struct ubifs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *ubifs_lookup(struct inode *dir, struct dentry *dentry,
				   unsigned int flags)
{
	int err;
	union ubifs_key key;
	struct inode *inode = NULL;
	struct ubifs_dent_node *dent = NULL;
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct fscrypt_name nm;

	dbg_gen("'%pd' in dir ino %lu", dentry, dir->i_ino);

	err = fscrypt_prepare_lookup(dir, dentry, &nm);
	if (err == -ENOENT)
		return d_splice_alias(NULL, dentry);
	if (err)
		return ERR_PTR(err);

	if (fname_len(&nm) > UBIFS_MAX_NLEN) {
		inode = ERR_PTR(-ENAMETOOLONG);
		goto done;
	}

	dent = kmalloc(UBIFS_MAX_DENT_NODE_SZ, GFP_NOFS);
	if (!dent) {
		inode = ERR_PTR(-ENOMEM);
		goto done;
	}

	if (nm.hash) {
		ubifs_assert(c, fname_len(&nm) == 0);
		ubifs_assert(c, fname_name(&nm) == NULL);
		dent_key_init_hash(c, &key, dir->i_ino, nm.hash);
		err = ubifs_tnc_lookup_dh(c, &key, dent, nm.minor_hash);
	} else {
		dent_key_init(c, &key, dir->i_ino, &nm);
		err = ubifs_tnc_lookup_nm(c, &key, dent, &nm);
	}

	if (err) {
		if (err == -ENOENT)
			dbg_gen("not found");
		else
			inode = ERR_PTR(err);
		goto done;
	}

	if (dbg_check_name(c, dent, &nm)) {
		inode = ERR_PTR(-EINVAL);
		goto done;
	}

	inode = ubifs_iget(dir->i_sb, le64_to_cpu(dent->inum));
	if (IS_ERR(inode)) {
		/*
		 * This should not happen. Probably the file-system needs
		 * checking.
		 */
		err = PTR_ERR(inode);
		ubifs_err(c, "dead directory entry '%pd', error %d",
			  dentry, err);
		ubifs_ro_mode(c, err);
		goto done;
	}

	if (ubifs_crypt_is_encrypted(dir) &&
	    (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) &&
	    !fscrypt_has_permitted_context(dir, inode)) {
		ubifs_warn(c, "Inconsistent encryption contexts: %lu/%lu",
			   dir->i_ino, inode->i_ino);
		iput(inode);
		inode = ERR_PTR(-EPERM);
	}

done:
	kfree(dent);
	fscrypt_free_filename(&nm);
	return d_splice_alias(inode, dentry);
}