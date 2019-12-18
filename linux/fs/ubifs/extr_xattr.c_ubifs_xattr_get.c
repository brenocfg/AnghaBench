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
struct ubifs_inode {size_t data_len; size_t xattr_size; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  data; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  inum; } ;
struct inode {size_t i_size; int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct fscrypt_name {int /*<<< orphan*/  disk_name; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  FSTR_INIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 scalar_t__ UBIFS_MAX_NLEN ; 
 int /*<<< orphan*/  UBIFS_MAX_XENT_NODE_SZ ; 
 scalar_t__ fname_len (struct fscrypt_name*) ; 
 struct inode* iget_xattr (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_tnc_lookup_nm (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,struct fscrypt_name*) ; 
 int /*<<< orphan*/  xent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,struct fscrypt_name*) ; 

ssize_t ubifs_xattr_get(struct inode *host, const char *name, void *buf,
			size_t size)
{
	struct inode *inode;
	struct ubifs_info *c = host->i_sb->s_fs_info;
	struct fscrypt_name nm = { .disk_name = FSTR_INIT((char *)name, strlen(name))};
	struct ubifs_inode *ui;
	struct ubifs_dent_node *xent;
	union ubifs_key key;
	int err;

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
		goto out_unlock;
	}

	inode = iget_xattr(c, le64_to_cpu(xent->inum));
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_unlock;
	}

	ui = ubifs_inode(inode);
	ubifs_assert(c, inode->i_size == ui->data_len);
	ubifs_assert(c, ubifs_inode(host)->xattr_size > ui->data_len);

	mutex_lock(&ui->ui_mutex);
	if (buf) {
		/* If @buf is %NULL we are supposed to return the length */
		if (ui->data_len > size) {
			err = -ERANGE;
			goto out_iput;
		}

		memcpy(buf, ui->data, ui->data_len);
	}
	err = ui->data_len;

out_iput:
	mutex_unlock(&ui->ui_mutex);
	iput(inode);
out_unlock:
	kfree(xent);
	return err;
}