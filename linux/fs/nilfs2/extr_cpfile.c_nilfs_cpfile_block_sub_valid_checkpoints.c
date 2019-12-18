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
struct nilfs_checkpoint {int /*<<< orphan*/  cp_checkpoints_count; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
nilfs_cpfile_block_sub_valid_checkpoints(const struct inode *cpfile,
					 struct buffer_head *bh,
					 void *kaddr,
					 unsigned int n)
{
	struct nilfs_checkpoint *cp = kaddr + bh_offset(bh);
	unsigned int count;

	WARN_ON(le32_to_cpu(cp->cp_checkpoints_count) < n);
	count = le32_to_cpu(cp->cp_checkpoints_count) - n;
	cp->cp_checkpoints_count = cpu_to_le32(count);
	return count;
}