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
struct qnx6_super_block {int /*<<< orphan*/  Longfile; int /*<<< orphan*/  Bitmap; int /*<<< orphan*/  Inode; int /*<<< orphan*/  sb_free_blocks; int /*<<< orphan*/  sb_num_blocks; int /*<<< orphan*/  sb_free_inodes; int /*<<< orphan*/  sb_num_inodes; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_serial; int /*<<< orphan*/  sb_checksum; int /*<<< orphan*/  sb_magic; } ;
struct qnx6_mmi_super_block {int /*<<< orphan*/  Longfile; int /*<<< orphan*/  Bitmap; int /*<<< orphan*/  Inode; int /*<<< orphan*/  sb_free_blocks; int /*<<< orphan*/  sb_num_blocks; int /*<<< orphan*/  sb_free_inodes; int /*<<< orphan*/  sb_num_inodes; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_serial; int /*<<< orphan*/  sb_checksum; int /*<<< orphan*/  sb_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qnx6_mmi_copy_sb(struct qnx6_super_block *qsb,
		struct qnx6_mmi_super_block *sb)
{
	qsb->sb_magic = sb->sb_magic;
	qsb->sb_checksum = sb->sb_checksum;
	qsb->sb_serial = sb->sb_serial;
	qsb->sb_blocksize = sb->sb_blocksize;
	qsb->sb_num_inodes = sb->sb_num_inodes;
	qsb->sb_free_inodes = sb->sb_free_inodes;
	qsb->sb_num_blocks = sb->sb_num_blocks;
	qsb->sb_free_blocks = sb->sb_free_blocks;

	/* the rest of the superblock is the same */
	memcpy(&qsb->Inode, &sb->Inode, sizeof(sb->Inode));
	memcpy(&qsb->Bitmap, &sb->Bitmap, sizeof(sb->Bitmap));
	memcpy(&qsb->Longfile, &sb->Longfile, sizeof(sb->Longfile));
}