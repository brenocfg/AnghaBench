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
struct ubifs_inode {int data_len; int xattr_cnt; int xattr_names; int xattr; int ui_size; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  xattr_size; int /*<<< orphan*/  data; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int new_ino; int new_dent; int dirtied_ino; int /*<<< orphan*/  dirtied_ino_d; int /*<<< orphan*/  new_ino_d; } ;
struct inode {int i_flags; int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ino; } ;
struct fscrypt_name {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 scalar_t__ CALC_DENT_SIZE (int) ; 
 scalar_t__ CALC_XATTR_BYTES (int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFREG ; 
 int S_IRWXUGO ; 
 int S_NOATIME ; 
 int S_NOCMTIME ; 
 int S_SYNC ; 
 int /*<<< orphan*/  UBIFS_CRYPT_FL ; 
 int /*<<< orphan*/  UBIFS_XATTR_FL ; 
 int /*<<< orphan*/  UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT ; 
 int XATTR_LIST_MAX ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  empty_aops ; 
 int /*<<< orphan*/  empty_fops ; 
 int /*<<< orphan*/  empty_iops ; 
 int fname_len (struct fscrypt_name const*) ; 
 int /*<<< orphan*/  fname_name (struct fscrypt_name const*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_update (struct ubifs_info*,struct inode*,struct fscrypt_name const*,struct inode*,int /*<<< orphan*/ ,int) ; 
 struct inode* ubifs_new_inode (struct ubifs_info*,struct inode*,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 
 int /*<<< orphan*/  ubifs_set_inode_flags (struct inode*) ; 
 int ubifs_xattr_max_cnt (struct ubifs_info*) ; 

__attribute__((used)) static int create_xattr(struct ubifs_info *c, struct inode *host,
			const struct fscrypt_name *nm, const void *value, int size)
{
	int err, names_len;
	struct inode *inode;
	struct ubifs_inode *ui, *host_ui = ubifs_inode(host);
	struct ubifs_budget_req req = { .new_ino = 1, .new_dent = 1,
				.new_ino_d = ALIGN(size, 8), .dirtied_ino = 1,
				.dirtied_ino_d = ALIGN(host_ui->data_len, 8) };

	if (host_ui->xattr_cnt >= ubifs_xattr_max_cnt(c)) {
		ubifs_err(c, "inode %lu already has too many xattrs (%d), cannot create more",
			  host->i_ino, host_ui->xattr_cnt);
		return -ENOSPC;
	}
	/*
	 * Linux limits the maximum size of the extended attribute names list
	 * to %XATTR_LIST_MAX. This means we should not allow creating more
	 * extended attributes if the name list becomes larger. This limitation
	 * is artificial for UBIFS, though.
	 */
	names_len = host_ui->xattr_names + host_ui->xattr_cnt + fname_len(nm) + 1;
	if (names_len > XATTR_LIST_MAX) {
		ubifs_err(c, "cannot add one more xattr name to inode %lu, total names length would become %d, max. is %d",
			  host->i_ino, names_len, XATTR_LIST_MAX);
		return -ENOSPC;
	}

	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	inode = ubifs_new_inode(c, host, S_IFREG | S_IRWXUGO);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_budg;
	}

	/* Re-define all operations to be "nothing" */
	inode->i_mapping->a_ops = &empty_aops;
	inode->i_op = &empty_iops;
	inode->i_fop = &empty_fops;

	inode->i_flags |= S_SYNC | S_NOATIME | S_NOCMTIME;
	ui = ubifs_inode(inode);
	ui->xattr = 1;
	ui->flags |= UBIFS_XATTR_FL;
	ui->data = kmemdup(value, size, GFP_NOFS);
	if (!ui->data) {
		err = -ENOMEM;
		goto out_free;
	}
	inode->i_size = ui->ui_size = size;
	ui->data_len = size;

	mutex_lock(&host_ui->ui_mutex);
	host->i_ctime = current_time(host);
	host_ui->xattr_cnt += 1;
	host_ui->xattr_size += CALC_DENT_SIZE(fname_len(nm));
	host_ui->xattr_size += CALC_XATTR_BYTES(size);
	host_ui->xattr_names += fname_len(nm);

	/*
	 * We handle UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT here because we
	 * have to set the UBIFS_CRYPT_FL flag on the host inode.
	 * To avoid multiple updates of the same inode in the same operation,
	 * let's do it here.
	 */
	if (strcmp(fname_name(nm), UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT) == 0)
		host_ui->flags |= UBIFS_CRYPT_FL;

	err = ubifs_jnl_update(c, host, nm, inode, 0, 1);
	if (err)
		goto out_cancel;
	ubifs_set_inode_flags(host);
	mutex_unlock(&host_ui->ui_mutex);

	ubifs_release_budget(c, &req);
	insert_inode_hash(inode);
	iput(inode);
	return 0;

out_cancel:
	host_ui->xattr_cnt -= 1;
	host_ui->xattr_size -= CALC_DENT_SIZE(fname_len(nm));
	host_ui->xattr_size -= CALC_XATTR_BYTES(size);
	host_ui->xattr_names -= fname_len(nm);
	host_ui->flags &= ~UBIFS_CRYPT_FL;
	mutex_unlock(&host_ui->ui_mutex);
out_free:
	make_bad_inode(inode);
	iput(inode);
out_budg:
	ubifs_release_budget(c, &req);
	return err;
}