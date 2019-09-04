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
struct inode_management {scalar_t__ ino_num; int /*<<< orphan*/  ino_list; int /*<<< orphan*/  ino_lock; int /*<<< orphan*/  ino_root; } ;
struct f2fs_sb_info {int max_orphans; int blocks_per_seg; struct inode_management* im; } ;

/* Variables and functions */
 int F2FS_CP_PACKS ; 
 int F2FS_ORPHANS_PER_BLOCK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_INO_ENTRY ; 
 int NR_CURSEG_TYPE ; 
 int __cp_payload (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void f2fs_init_ino_entry_info(struct f2fs_sb_info *sbi)
{
	int i;

	for (i = 0; i < MAX_INO_ENTRY; i++) {
		struct inode_management *im = &sbi->im[i];

		INIT_RADIX_TREE(&im->ino_root, GFP_ATOMIC);
		spin_lock_init(&im->ino_lock);
		INIT_LIST_HEAD(&im->ino_list);
		im->ino_num = 0;
	}

	sbi->max_orphans = (sbi->blocks_per_seg - F2FS_CP_PACKS -
			NR_CURSEG_TYPE - __cp_payload(sbi)) *
				F2FS_ORPHANS_PER_BLOCK;
}