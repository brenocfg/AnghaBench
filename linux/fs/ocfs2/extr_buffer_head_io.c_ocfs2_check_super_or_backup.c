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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int OCFS2_MAX_BACKUP_SUPERBLOCKS ; 
 scalar_t__ OCFS2_SUPER_BLOCK_BLKNO ; 
 scalar_t__ ocfs2_backup_super_blkno (struct super_block*,int) ; 

__attribute__((used)) static void ocfs2_check_super_or_backup(struct super_block *sb,
					sector_t blkno)
{
	int i;
	u64 backup_blkno;

	if (blkno == OCFS2_SUPER_BLOCK_BLKNO)
		return;

	for (i = 0; i < OCFS2_MAX_BACKUP_SUPERBLOCKS; i++) {
		backup_blkno = ocfs2_backup_super_blkno(sb, i);
		if (backup_blkno == blkno)
			return;
	}

	BUG();
}