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
struct inode {int i_nlink; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int /*<<< orphan*/  disk_name; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSTR_INIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 scalar_t__ UBIFS_MAX_NLEN ; 
 int /*<<< orphan*/  UBIFS_MAX_XENT_NODE_SZ ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 scalar_t__ fname_len (struct fscrypt_name*) ; 
 struct inode* iget_xattr (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int remove_xattr (struct ubifs_info*,struct inode*,struct inode*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_tnc_lookup_nm (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  xent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,struct fscrypt_name*) ; 

__attribute__((used)) static int ubifs_xattr_remove(struct inode *host, const char *name)
{
	struct inode *inode;
	struct ubifs_info *c = host->i_sb->s_fs_info;
	struct fscrypt_name nm = { .disk_name = FSTR_INIT((char *)name, strlen(name))};
	struct ubifs_dent_node *xent;
	union ubifs_key key;
	int err;

	ubifs_assert(c, inode_is_locked(host));

	if (fname_len(&nm) > UBIFS_MAX_NLEN)
		return -ENAMETOOLONG;

	xent = kmalloc(UBIFS_MAX_XENT_NODE_SZ, GFP_NOFS);
	if (!xent)
		return -ENOMEM;

	xent_key_init(c, &key, host->i_ino, &nm);
	err = ubifs_tnc_lookup_nm(c, &key, xent, &nm);
	if (err) {
		if (err == -ENOENT)
			err = -ENODATA;
		goto out_free;
	}

	inode = iget_xattr(c, le64_to_cpu(xent->inum));
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_free;
	}

	ubifs_assert(c, inode->i_nlink == 1);
	clear_nlink(inode);
	err = remove_xattr(c, host, inode, &nm);
	if (err)
		set_nlink(inode, 1);

	/* If @i_nlink is 0, 'iput()' will delete the inode */
	iput(inode);

out_free:
	kfree(xent);
	return err;
}