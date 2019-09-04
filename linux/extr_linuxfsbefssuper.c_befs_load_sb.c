#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct befs_sb_info {int /*<<< orphan*/ * nls; void* indices; void* root_dir; void* log_end; void* log_start; void* log_blocks; void* flags; void* num_ags; void* ag_shift; void* blocks_per_ag; void* inode_size; void* used_blocks; void* num_blocks; void* block_shift; void* block_size; void* magic3; void* magic2; void* magic1; int /*<<< orphan*/  byte_order; } ;
struct TYPE_3__ {scalar_t__ fs_byte_order; int /*<<< orphan*/  indices; int /*<<< orphan*/  root_dir; int /*<<< orphan*/  log_end; int /*<<< orphan*/  log_start; int /*<<< orphan*/  log_blocks; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_ags; int /*<<< orphan*/  ag_shift; int /*<<< orphan*/  blocks_per_ag; int /*<<< orphan*/  inode_size; int /*<<< orphan*/  used_blocks; int /*<<< orphan*/  num_blocks; int /*<<< orphan*/  block_shift; int /*<<< orphan*/  block_size; int /*<<< orphan*/  magic3; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; } ;
typedef  TYPE_1__ befs_super_block ;

/* Variables and functions */
 scalar_t__ BEFS_BYTEORDER_NATIVE_BE ; 
 scalar_t__ BEFS_BYTEORDER_NATIVE_LE ; 
 int /*<<< orphan*/  BEFS_BYTESEX_BE ; 
 int /*<<< orphan*/  BEFS_BYTESEX_LE ; 
 int BEFS_OK ; 
 struct befs_sb_info* BEFS_SB (struct super_block*) ; 
 void* fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fsrun_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

int
befs_load_sb(struct super_block *sb, befs_super_block *disk_sb)
{
	struct befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check the byte order of the filesystem */
	if (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_LE)
		befs_sb->byte_order = BEFS_BYTESEX_LE;
	else if (disk_sb->fs_byte_order == BEFS_BYTEORDER_NATIVE_BE)
		befs_sb->byte_order = BEFS_BYTESEX_BE;

	befs_sb->magic1 = fs32_to_cpu(sb, disk_sb->magic1);
	befs_sb->magic2 = fs32_to_cpu(sb, disk_sb->magic2);
	befs_sb->magic3 = fs32_to_cpu(sb, disk_sb->magic3);
	befs_sb->block_size = fs32_to_cpu(sb, disk_sb->block_size);
	befs_sb->block_shift = fs32_to_cpu(sb, disk_sb->block_shift);
	befs_sb->num_blocks = fs64_to_cpu(sb, disk_sb->num_blocks);
	befs_sb->used_blocks = fs64_to_cpu(sb, disk_sb->used_blocks);
	befs_sb->inode_size = fs32_to_cpu(sb, disk_sb->inode_size);

	befs_sb->blocks_per_ag = fs32_to_cpu(sb, disk_sb->blocks_per_ag);
	befs_sb->ag_shift = fs32_to_cpu(sb, disk_sb->ag_shift);
	befs_sb->num_ags = fs32_to_cpu(sb, disk_sb->num_ags);

	befs_sb->flags = fs32_to_cpu(sb, disk_sb->flags);

	befs_sb->log_blocks = fsrun_to_cpu(sb, disk_sb->log_blocks);
	befs_sb->log_start = fs64_to_cpu(sb, disk_sb->log_start);
	befs_sb->log_end = fs64_to_cpu(sb, disk_sb->log_end);

	befs_sb->root_dir = fsrun_to_cpu(sb, disk_sb->root_dir);
	befs_sb->indices = fsrun_to_cpu(sb, disk_sb->indices);
	befs_sb->nls = NULL;

	return BEFS_OK;
}