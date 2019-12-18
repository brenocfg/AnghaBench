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
struct ubifs_inode {scalar_t__ ui_size; scalar_t__ synced_i_size; int /*<<< orphan*/  ui_mutex; int /*<<< orphan*/  ui_lock; int /*<<< orphan*/  dirty; } ;
struct ubifs_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_is_chk_gen (struct ubifs_info const*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info const*,char*,scalar_t__,scalar_t__,...) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 

int dbg_check_synced_i_size(const struct ubifs_info *c, struct inode *inode)
{
	int err = 0;
	struct ubifs_inode *ui = ubifs_inode(inode);

	if (!dbg_is_chk_gen(c))
		return 0;
	if (!S_ISREG(inode->i_mode))
		return 0;

	mutex_lock(&ui->ui_mutex);
	spin_lock(&ui->ui_lock);
	if (ui->ui_size != ui->synced_i_size && !ui->dirty) {
		ubifs_err(c, "ui_size is %lld, synced_i_size is %lld, but inode is clean",
			  ui->ui_size, ui->synced_i_size);
		ubifs_err(c, "i_ino %lu, i_mode %#x, i_size %lld", inode->i_ino,
			  inode->i_mode, i_size_read(inode));
		dump_stack();
		err = -EINVAL;
	}
	spin_unlock(&ui->ui_lock);
	mutex_unlock(&ui->ui_mutex);
	return err;
}