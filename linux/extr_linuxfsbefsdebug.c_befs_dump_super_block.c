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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  befs_super_block ;

/* Variables and functions */

void
befs_dump_super_block(const struct super_block *sb, befs_super_block *sup)
{
#ifdef CONFIG_BEFS_DEBUG

	befs_block_run tmp_run;

	befs_debug(sb, "befs_super_block information");

	befs_debug(sb, "  name %s", sup->name);
	befs_debug(sb, "  magic1 %08x", fs32_to_cpu(sb, sup->magic1));
	befs_debug(sb, "  fs_byte_order %08x",
		   fs32_to_cpu(sb, sup->fs_byte_order));

	befs_debug(sb, "  block_size %u", fs32_to_cpu(sb, sup->block_size));
	befs_debug(sb, "  block_shift %u", fs32_to_cpu(sb, sup->block_shift));

	befs_debug(sb, "  num_blocks %llu", fs64_to_cpu(sb, sup->num_blocks));
	befs_debug(sb, "  used_blocks %llu", fs64_to_cpu(sb, sup->used_blocks));
	befs_debug(sb, "  inode_size %u", fs32_to_cpu(sb, sup->inode_size));

	befs_debug(sb, "  magic2 %08x", fs32_to_cpu(sb, sup->magic2));
	befs_debug(sb, "  blocks_per_ag %u",
		   fs32_to_cpu(sb, sup->blocks_per_ag));
	befs_debug(sb, "  ag_shift %u", fs32_to_cpu(sb, sup->ag_shift));
	befs_debug(sb, "  num_ags %u", fs32_to_cpu(sb, sup->num_ags));

	befs_debug(sb, "  flags %08x", fs32_to_cpu(sb, sup->flags));

	tmp_run = fsrun_to_cpu(sb, sup->log_blocks);
	befs_debug(sb, "  log_blocks %u, %hu, %hu",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

	befs_debug(sb, "  log_start %lld", fs64_to_cpu(sb, sup->log_start));
	befs_debug(sb, "  log_end %lld", fs64_to_cpu(sb, sup->log_end));

	befs_debug(sb, "  magic3 %08x", fs32_to_cpu(sb, sup->magic3));

	tmp_run = fsrun_to_cpu(sb, sup->root_dir);
	befs_debug(sb, "  root_dir %u, %hu, %hu",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

	tmp_run = fsrun_to_cpu(sb, sup->indices);
	befs_debug(sb, "  indices %u, %hu, %hu",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

#endif				//CONFIG_BEFS_DEBUG
}