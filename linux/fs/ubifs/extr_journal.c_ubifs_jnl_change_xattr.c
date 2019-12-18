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
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_wbuf {int dummy; } ;
struct ubifs_inode {int data_len; int /*<<< orphan*/  ui_lock; int /*<<< orphan*/  ui_size; int /*<<< orphan*/  synced_i_size; int /*<<< orphan*/  ui_mutex; } ;
typedef  void ubifs_ino_node ;
struct ubifs_info {TYPE_1__* jheads; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 size_t BASEHD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int IS_DIRSYNC (struct inode const*) ; 
 int UBIFS_HASH_ARR_SZ ; 
 int UBIFS_INO_NODE_SZ ; 
 int /*<<< orphan*/  dbg_jnl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_reservation (struct ubifs_info*) ; 
 int /*<<< orphan*/  ino_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int make_reservation (struct ubifs_info*,size_t,int) ; 
 int /*<<< orphan*/  mark_inode_clean (struct ubifs_info*,struct ubifs_inode*) ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_inode (struct ubifs_info*,void*,struct inode const*,int) ; 
 int /*<<< orphan*/  release_head (struct ubifs_info*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_add_auth_dirt (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ ubifs_auth_node_sz (struct ubifs_info*) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int ubifs_node_calc_hash (struct ubifs_info*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_add (struct ubifs_info*,union ubifs_key*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_wbuf_add_ino_nolock (struct ubifs_wbuf*,int /*<<< orphan*/ ) ; 
 int write_head (struct ubifs_info*,size_t,void*,int,int*,int*,int /*<<< orphan*/ ) ; 

int ubifs_jnl_change_xattr(struct ubifs_info *c, const struct inode *inode,
			   const struct inode *host)
{
	int err, len1, len2, aligned_len, aligned_len1, lnum, offs;
	struct ubifs_inode *host_ui = ubifs_inode(host);
	struct ubifs_ino_node *ino;
	union ubifs_key key;
	int sync = IS_DIRSYNC(host);
	u8 hash_host[UBIFS_HASH_ARR_SZ];
	u8 hash[UBIFS_HASH_ARR_SZ];

	dbg_jnl("ino %lu, ino %lu", host->i_ino, inode->i_ino);
	ubifs_assert(c, host->i_nlink > 0);
	ubifs_assert(c, inode->i_nlink > 0);
	ubifs_assert(c, mutex_is_locked(&host_ui->ui_mutex));

	len1 = UBIFS_INO_NODE_SZ + host_ui->data_len;
	len2 = UBIFS_INO_NODE_SZ + ubifs_inode(inode)->data_len;
	aligned_len1 = ALIGN(len1, 8);
	aligned_len = aligned_len1 + ALIGN(len2, 8);

	aligned_len += ubifs_auth_node_sz(c);

	ino = kzalloc(aligned_len, GFP_NOFS);
	if (!ino)
		return -ENOMEM;

	/* Make reservation before allocating sequence numbers */
	err = make_reservation(c, BASEHD, aligned_len);
	if (err)
		goto out_free;

	pack_inode(c, ino, host, 0);
	err = ubifs_node_calc_hash(c, ino, hash_host);
	if (err)
		goto out_release;
	pack_inode(c, (void *)ino + aligned_len1, inode, 1);
	err = ubifs_node_calc_hash(c, (void *)ino + aligned_len1, hash);
	if (err)
		goto out_release;

	err = write_head(c, BASEHD, ino, aligned_len, &lnum, &offs, 0);
	if (!sync && !err) {
		struct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nolock(wbuf, host->i_ino);
		ubifs_wbuf_add_ino_nolock(wbuf, inode->i_ino);
	}
	release_head(c, BASEHD);
	if (err)
		goto out_ro;

	ubifs_add_auth_dirt(c, lnum);

	ino_key_init(c, &key, host->i_ino);
	err = ubifs_tnc_add(c, &key, lnum, offs, len1, hash_host);
	if (err)
		goto out_ro;

	ino_key_init(c, &key, inode->i_ino);
	err = ubifs_tnc_add(c, &key, lnum, offs + aligned_len1, len2, hash);
	if (err)
		goto out_ro;

	finish_reservation(c);
	spin_lock(&host_ui->ui_lock);
	host_ui->synced_i_size = host_ui->ui_size;
	spin_unlock(&host_ui->ui_lock);
	mark_inode_clean(c, host_ui);
	kfree(ino);
	return 0;

out_release:
	release_head(c, BASEHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	kfree(ino);
	return err;
}