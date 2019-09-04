#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nfs; } ;
struct msdos_sb_info {int /*<<< orphan*/  dir_hash_lock; struct hlist_head* dir_hashtable; TYPE_1__ options; int /*<<< orphan*/  inode_hash_lock; struct hlist_head* inode_hashtable; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_dir_hash; int /*<<< orphan*/  i_logstart; int /*<<< orphan*/  i_fat_hash; int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_I (struct inode*) ; 
 scalar_t__ MSDOS_ROOT_INO ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_dir_hash (int /*<<< orphan*/ ) ; 
 int fat_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fat_attach(struct inode *inode, loff_t i_pos)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);

	if (inode->i_ino != MSDOS_ROOT_INO) {
		struct hlist_head *head =   sbi->inode_hashtable
					  + fat_hash(i_pos);

		spin_lock(&sbi->inode_hash_lock);
		MSDOS_I(inode)->i_pos = i_pos;
		hlist_add_head(&MSDOS_I(inode)->i_fat_hash, head);
		spin_unlock(&sbi->inode_hash_lock);
	}

	/* If NFS support is enabled, cache the mapping of start cluster
	 * to directory inode. This is used during reconnection of
	 * dentries to the filesystem root.
	 */
	if (S_ISDIR(inode->i_mode) && sbi->options.nfs) {
		struct hlist_head *d_head = sbi->dir_hashtable;
		d_head += fat_dir_hash(MSDOS_I(inode)->i_logstart);

		spin_lock(&sbi->dir_hash_lock);
		hlist_add_head(&MSDOS_I(inode)->i_dir_hash, d_head);
		spin_unlock(&sbi->dir_hash_lock);
	}
}