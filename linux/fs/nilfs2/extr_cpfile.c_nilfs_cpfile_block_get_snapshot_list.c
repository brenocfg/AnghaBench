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
struct nilfs_snapshot_list {int dummy; } ;
struct nilfs_cpfile_header {struct nilfs_snapshot_list ch_snapshot_list; } ;
struct nilfs_checkpoint {struct nilfs_snapshot_list cp_snapshot_list; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 struct nilfs_checkpoint* nilfs_cpfile_block_get_checkpoint (struct inode const*,scalar_t__,struct buffer_head*,void*) ; 
 struct nilfs_cpfile_header* nilfs_cpfile_block_get_header (struct inode const*,struct buffer_head*,void*) ; 

__attribute__((used)) static struct nilfs_snapshot_list *
nilfs_cpfile_block_get_snapshot_list(const struct inode *cpfile,
				     __u64 cno,
				     struct buffer_head *bh,
				     void *kaddr)
{
	struct nilfs_cpfile_header *header;
	struct nilfs_checkpoint *cp;
	struct nilfs_snapshot_list *list;

	if (cno != 0) {
		cp = nilfs_cpfile_block_get_checkpoint(cpfile, cno, bh, kaddr);
		list = &cp->cp_snapshot_list;
	} else {
		header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
		list = &header->ch_snapshot_list;
	}
	return list;
}