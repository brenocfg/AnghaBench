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
typedef  int /*<<< orphan*/  befs_inode ;

/* Variables and functions */

void
befs_dump_inode(const struct super_block *sb, befs_inode *inode)
{
#ifdef CONFIG_BEFS_DEBUG

	befs_block_run tmp_run;

	befs_debug(sb, "befs_inode information");

	befs_debug(sb, "  magic1 %08x", fs32_to_cpu(sb, inode->magic1));

	tmp_run = fsrun_to_cpu(sb, inode->inode_num);
	befs_debug(sb, "  inode_num %u, %hu, %hu",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

	befs_debug(sb, "  uid %u", fs32_to_cpu(sb, inode->uid));
	befs_debug(sb, "  gid %u", fs32_to_cpu(sb, inode->gid));
	befs_debug(sb, "  mode %08x", fs32_to_cpu(sb, inode->mode));
	befs_debug(sb, "  flags %08x", fs32_to_cpu(sb, inode->flags));
	befs_debug(sb, "  create_time %llu",
		   fs64_to_cpu(sb, inode->create_time));
	befs_debug(sb, "  last_modified_time %llu",
		   fs64_to_cpu(sb, inode->last_modified_time));

	tmp_run = fsrun_to_cpu(sb, inode->parent);
	befs_debug(sb, "  parent [%u, %hu, %hu]",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

	tmp_run = fsrun_to_cpu(sb, inode->attributes);
	befs_debug(sb, "  attributes [%u, %hu, %hu]",
		   tmp_run.allocation_group, tmp_run.start, tmp_run.len);

	befs_debug(sb, "  type %08x", fs32_to_cpu(sb, inode->type));
	befs_debug(sb, "  inode_size %u", fs32_to_cpu(sb, inode->inode_size));

	if (S_ISLNK(fs32_to_cpu(sb, inode->mode))) {
		befs_debug(sb, "  Symbolic link [%s]", inode->data.symlink);
	} else {
		int i;

		for (i = 0; i < BEFS_NUM_DIRECT_BLOCKS; i++) {
			tmp_run =
			    fsrun_to_cpu(sb, inode->data.datastream.direct[i]);
			befs_debug(sb, "  direct %d [%u, %hu, %hu]", i,
				   tmp_run.allocation_group, tmp_run.start,
				   tmp_run.len);
		}
		befs_debug(sb, "  max_direct_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_direct_range));

		tmp_run = fsrun_to_cpu(sb, inode->data.datastream.indirect);
		befs_debug(sb, "  indirect [%u, %hu, %hu]",
			   tmp_run.allocation_group,
			   tmp_run.start, tmp_run.len);

		befs_debug(sb, "  max_indirect_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_indirect_range));

		tmp_run =
		    fsrun_to_cpu(sb, inode->data.datastream.double_indirect);
		befs_debug(sb, "  double indirect [%u, %hu, %hu]",
			   tmp_run.allocation_group, tmp_run.start,
			   tmp_run.len);

		befs_debug(sb, "  max_double_indirect_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_double_indirect_range));

		befs_debug(sb, "  size %llu",
			   fs64_to_cpu(sb, inode->data.datastream.size));
	}

#endif				//CONFIG_BEFS_DEBUG
}