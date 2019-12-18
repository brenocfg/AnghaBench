#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
union ubifs_dev_desc {int /*<<< orphan*/  huge; int /*<<< orphan*/  new; } ;
struct ubifs_inode {size_t data_len; int flags; int xattr; void* data; void* ui_size; void* synced_i_size; void* xattr_names; void* xattr_size; void* xattr_cnt; void* creat_sqnum; int /*<<< orphan*/  compr_type; } ;
struct ubifs_ino_node {scalar_t__ data; int /*<<< orphan*/  xattr_names; int /*<<< orphan*/  xattr_size; int /*<<< orphan*/  xattr_cnt; int /*<<< orphan*/  creat_sqnum; int /*<<< orphan*/  compr_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_len; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  ctime_nsec; int /*<<< orphan*/  ctime_sec; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime_sec; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime_sec; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; } ;
struct ubifs_info {int dummy; } ;
struct super_block {struct ubifs_info* s_fs_info; } ;
struct TYPE_7__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_6__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_5__ {void* tv_nsec; void* tv_sec; } ;
struct inode {int i_state; int i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; TYPE_4__* i_mapping; void* i_size; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; int /*<<< orphan*/  i_flags; } ;
typedef  void* int64_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_8__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_UBIFS_ATIME_SUPPORT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  S_NOATIME ; 
 int /*<<< orphan*/  S_NOCMTIME ; 
 size_t UBIFS_MAX_INO_DATA ; 
 int UBIFS_MAX_INO_NODE_SZ ; 
 int UBIFS_XATTR_FL ; 
 int /*<<< orphan*/  dbg_gen (char*,unsigned long) ; 
 int /*<<< orphan*/  huge_decode_dev (void*) ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,void*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ubifs_ino_node*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  new_decode_dev (void*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,void*) ; 
 int /*<<< orphan*/  ubifs_dir_inode_operations ; 
 int /*<<< orphan*/  ubifs_dir_operations ; 
 int /*<<< orphan*/  ubifs_dump_inode (struct ubifs_info*,struct inode*) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,struct ubifs_ino_node*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_file_address_operations ; 
 int /*<<< orphan*/  ubifs_file_inode_operations ; 
 int /*<<< orphan*/  ubifs_file_operations ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  ubifs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ubifs_symlink_inode_operations ; 
 int ubifs_tnc_lookup (struct ubifs_info*,union ubifs_key*,struct ubifs_ino_node*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 int validate_inode (struct ubifs_info*,struct inode*) ; 

struct inode *ubifs_iget(struct super_block *sb, unsigned long inum)
{
	int err;
	union ubifs_key key;
	struct ubifs_ino_node *ino;
	struct ubifs_info *c = sb->s_fs_info;
	struct inode *inode;
	struct ubifs_inode *ui;

	dbg_gen("inode %lu", inum);

	inode = iget_locked(sb, inum);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;
	ui = ubifs_inode(inode);

	ino = kmalloc(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	if (!ino) {
		err = -ENOMEM;
		goto out;
	}

	ino_key_init(c, &key, inode->i_ino);

	err = ubifs_tnc_lookup(c, &key, ino);
	if (err)
		goto out_ino;

	inode->i_flags |= S_NOCMTIME;

	if (!IS_ENABLED(CONFIG_UBIFS_ATIME_SUPPORT))
		inode->i_flags |= S_NOATIME;

	set_nlink(inode, le32_to_cpu(ino->nlink));
	i_uid_write(inode, le32_to_cpu(ino->uid));
	i_gid_write(inode, le32_to_cpu(ino->gid));
	inode->i_atime.tv_sec  = (int64_t)le64_to_cpu(ino->atime_sec);
	inode->i_atime.tv_nsec = le32_to_cpu(ino->atime_nsec);
	inode->i_mtime.tv_sec  = (int64_t)le64_to_cpu(ino->mtime_sec);
	inode->i_mtime.tv_nsec = le32_to_cpu(ino->mtime_nsec);
	inode->i_ctime.tv_sec  = (int64_t)le64_to_cpu(ino->ctime_sec);
	inode->i_ctime.tv_nsec = le32_to_cpu(ino->ctime_nsec);
	inode->i_mode = le32_to_cpu(ino->mode);
	inode->i_size = le64_to_cpu(ino->size);

	ui->data_len    = le32_to_cpu(ino->data_len);
	ui->flags       = le32_to_cpu(ino->flags);
	ui->compr_type  = le16_to_cpu(ino->compr_type);
	ui->creat_sqnum = le64_to_cpu(ino->creat_sqnum);
	ui->xattr_cnt   = le32_to_cpu(ino->xattr_cnt);
	ui->xattr_size  = le32_to_cpu(ino->xattr_size);
	ui->xattr_names = le32_to_cpu(ino->xattr_names);
	ui->synced_i_size = ui->ui_size = inode->i_size;

	ui->xattr = (ui->flags & UBIFS_XATTR_FL) ? 1 : 0;

	err = validate_inode(c, inode);
	if (err)
		goto out_invalid;

	switch (inode->i_mode & S_IFMT) {
	case S_IFREG:
		inode->i_mapping->a_ops = &ubifs_file_address_operations;
		inode->i_op = &ubifs_file_inode_operations;
		inode->i_fop = &ubifs_file_operations;
		if (ui->xattr) {
			ui->data = kmalloc(ui->data_len + 1, GFP_NOFS);
			if (!ui->data) {
				err = -ENOMEM;
				goto out_ino;
			}
			memcpy(ui->data, ino->data, ui->data_len);
			((char *)ui->data)[ui->data_len] = '\0';
		} else if (ui->data_len != 0) {
			err = 10;
			goto out_invalid;
		}
		break;
	case S_IFDIR:
		inode->i_op  = &ubifs_dir_inode_operations;
		inode->i_fop = &ubifs_dir_operations;
		if (ui->data_len != 0) {
			err = 11;
			goto out_invalid;
		}
		break;
	case S_IFLNK:
		inode->i_op = &ubifs_symlink_inode_operations;
		if (ui->data_len <= 0 || ui->data_len > UBIFS_MAX_INO_DATA) {
			err = 12;
			goto out_invalid;
		}
		ui->data = kmalloc(ui->data_len + 1, GFP_NOFS);
		if (!ui->data) {
			err = -ENOMEM;
			goto out_ino;
		}
		memcpy(ui->data, ino->data, ui->data_len);
		((char *)ui->data)[ui->data_len] = '\0';
		break;
	case S_IFBLK:
	case S_IFCHR:
	{
		dev_t rdev;
		union ubifs_dev_desc *dev;

		ui->data = kmalloc(sizeof(union ubifs_dev_desc), GFP_NOFS);
		if (!ui->data) {
			err = -ENOMEM;
			goto out_ino;
		}

		dev = (union ubifs_dev_desc *)ino->data;
		if (ui->data_len == sizeof(dev->new))
			rdev = new_decode_dev(le32_to_cpu(dev->new));
		else if (ui->data_len == sizeof(dev->huge))
			rdev = huge_decode_dev(le64_to_cpu(dev->huge));
		else {
			err = 13;
			goto out_invalid;
		}
		memcpy(ui->data, ino->data, ui->data_len);
		inode->i_op = &ubifs_file_inode_operations;
		init_special_inode(inode, inode->i_mode, rdev);
		break;
	}
	case S_IFSOCK:
	case S_IFIFO:
		inode->i_op = &ubifs_file_inode_operations;
		init_special_inode(inode, inode->i_mode, 0);
		if (ui->data_len != 0) {
			err = 14;
			goto out_invalid;
		}
		break;
	default:
		err = 15;
		goto out_invalid;
	}

	kfree(ino);
	ubifs_set_inode_flags(inode);
	unlock_new_inode(inode);
	return inode;

out_invalid:
	ubifs_err(c, "inode %lu validation failed, error %d", inode->i_ino, err);
	ubifs_dump_node(c, ino);
	ubifs_dump_inode(c, inode);
	err = -EINVAL;
out_ino:
	kfree(ino);
out:
	ubifs_err(c, "failed to read inode %lu, error %d", inode->i_ino, err);
	iget_failed(inode);
	return ERR_PTR(err);
}