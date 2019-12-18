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
struct ubifs_inode {int data_len; int ui_size; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  xattr_size; void* data; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_budget_req {int dirtied_ino; scalar_t__ dirtied_ino_d; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 scalar_t__ CALC_XATTR_BYTES (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_budget_space (struct ubifs_info*,struct ubifs_budget_req*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_change_xattr (struct ubifs_info*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

__attribute__((used)) static int change_xattr(struct ubifs_info *c, struct inode *host,
			struct inode *inode, const void *value, int size)
{
	int err;
	struct ubifs_inode *host_ui = ubifs_inode(host);
	struct ubifs_inode *ui = ubifs_inode(inode);
	void *buf = NULL;
	int old_size;
	struct ubifs_budget_req req = { .dirtied_ino = 2,
		.dirtied_ino_d = ALIGN(size, 8) + ALIGN(host_ui->data_len, 8) };

	ubifs_assert(c, ui->data_len == inode->i_size);
	err = ubifs_budget_space(c, &req);
	if (err)
		return err;

	buf = kmemdup(value, size, GFP_NOFS);
	if (!buf) {
		err = -ENOMEM;
		goto out_free;
	}
	mutex_lock(&ui->ui_mutex);
	kfree(ui->data);
	ui->data = buf;
	inode->i_size = ui->ui_size = size;
	old_size = ui->data_len;
	ui->data_len = size;
	mutex_unlock(&ui->ui_mutex);

	mutex_lock(&host_ui->ui_mutex);
	host->i_ctime = current_time(host);
	host_ui->xattr_size -= CALC_XATTR_BYTES(old_size);
	host_ui->xattr_size += CALC_XATTR_BYTES(size);

	/*
	 * It is important to write the host inode after the xattr inode
	 * because if the host inode gets synchronized (via 'fsync()'), then
	 * the extended attribute inode gets synchronized, because it goes
	 * before the host inode in the write-buffer.
	 */
	err = ubifs_jnl_change_xattr(c, inode, host);
	if (err)
		goto out_cancel;
	mutex_unlock(&host_ui->ui_mutex);

	ubifs_release_budget(c, &req);
	return 0;

out_cancel:
	host_ui->xattr_size -= CALC_XATTR_BYTES(size);
	host_ui->xattr_size += CALC_XATTR_BYTES(old_size);
	mutex_unlock(&host_ui->ui_mutex);
	make_bad_inode(inode);
out_free:
	ubifs_release_budget(c, &req);
	return err;
}