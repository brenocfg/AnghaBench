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
struct ubifs_inode {scalar_t__ ui_size; scalar_t__ synced_i_size; } ;
struct ubifs_info {int /*<<< orphan*/  size_tree; scalar_t__ ro_mount; int /*<<< orphan*/  vfs_sb; } ;
struct size_entry {scalar_t__ d_size; int /*<<< orphan*/  rb; struct inode* inode; scalar_t__ inum; } ;
struct inode {scalar_t__ i_size; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  dbg_rcvry (char*,unsigned long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct size_entry*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 struct inode* ubifs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int ubifs_jnl_write_inode (struct ubifs_info*,struct inode*) ; 

__attribute__((used)) static int inode_fix_size(struct ubifs_info *c, struct size_entry *e)
{
	struct inode *inode;
	struct ubifs_inode *ui;
	int err;

	if (c->ro_mount)
		ubifs_assert(c, !e->inode);

	if (e->inode) {
		/* Remounting rw, pick up inode we stored earlier */
		inode = e->inode;
	} else {
		inode = ubifs_iget(c->vfs_sb, e->inum);
		if (IS_ERR(inode))
			return PTR_ERR(inode);

		if (inode->i_size >= e->d_size) {
			/*
			 * The original inode in the index already has a size
			 * big enough, nothing to do
			 */
			iput(inode);
			return 0;
		}

		dbg_rcvry("ino %lu size %lld -> %lld",
			  (unsigned long)e->inum,
			  inode->i_size, e->d_size);

		ui = ubifs_inode(inode);

		inode->i_size = e->d_size;
		ui->ui_size = e->d_size;
		ui->synced_i_size = e->d_size;

		e->inode = inode;
	}

	/*
	 * In readonly mode just keep the inode pinned in memory until we go
	 * readwrite. In readwrite mode write the inode to the journal with the
	 * fixed size.
	 */
	if (c->ro_mount)
		return 0;

	err = ubifs_jnl_write_inode(c, inode);

	iput(inode);

	if (err)
		return err;

	rb_erase(&e->rb, &c->size_tree);
	kfree(e);

	return 0;
}