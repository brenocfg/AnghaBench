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
struct msdos_sb_info {int /*<<< orphan*/  dir_hash_lock; TYPE_1__ options; int /*<<< orphan*/  inode_hash_lock; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_dir_hash; int /*<<< orphan*/  i_fat_hash; scalar_t__ i_pos; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_I (struct inode*) ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fat_detach(struct inode *inode)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	spin_lock(&sbi->inode_hash_lock);
	MSDOS_I(inode)->i_pos = 0;
	hlist_del_init(&MSDOS_I(inode)->i_fat_hash);
	spin_unlock(&sbi->inode_hash_lock);

	if (S_ISDIR(inode->i_mode) && sbi->options.nfs) {
		spin_lock(&sbi->dir_hash_lock);
		hlist_del_init(&MSDOS_I(inode)->i_dir_hash);
		spin_unlock(&sbi->dir_hash_lock);
	}
}