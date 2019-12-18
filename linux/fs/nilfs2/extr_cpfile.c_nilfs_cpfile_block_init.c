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
struct nilfs_checkpoint {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {size_t mi_entry_size; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_checkpoint_set_invalid (struct nilfs_checkpoint*) ; 
 int nilfs_cpfile_checkpoints_per_block (struct inode*) ; 

__attribute__((used)) static void nilfs_cpfile_block_init(struct inode *cpfile,
				    struct buffer_head *bh,
				    void *kaddr)
{
	struct nilfs_checkpoint *cp = kaddr + bh_offset(bh);
	size_t cpsz = NILFS_MDT(cpfile)->mi_entry_size;
	int n = nilfs_cpfile_checkpoints_per_block(cpfile);

	while (n-- > 0) {
		nilfs_checkpoint_set_invalid(cp);
		cp = (void *)cp + cpsz;
	}
}