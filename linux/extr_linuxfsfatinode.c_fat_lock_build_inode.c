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
struct TYPE_2__ {scalar_t__ nfs; } ;
struct msdos_sb_info {int /*<<< orphan*/  nfs_build_inode_lock; TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ FAT_NFS_NOSTALE_RO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fat_lock_build_inode(struct msdos_sb_info *sbi)
{
	if (sbi->options.nfs == FAT_NFS_NOSTALE_RO)
		mutex_lock(&sbi->nfs_build_inode_lock);
}