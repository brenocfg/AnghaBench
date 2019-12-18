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
struct nilfs_mdt_info {unsigned int mi_entry_size; unsigned int mi_entries_per_block; int /*<<< orphan*/  mi_first_entry_offset; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,unsigned int) ; 
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 unsigned int i_blocksize (struct inode*) ; 

void nilfs_mdt_set_entry_size(struct inode *inode, unsigned int entry_size,
			      unsigned int header_size)
{
	struct nilfs_mdt_info *mi = NILFS_MDT(inode);

	mi->mi_entry_size = entry_size;
	mi->mi_entries_per_block = i_blocksize(inode) / entry_size;
	mi->mi_first_entry_offset = DIV_ROUND_UP(header_size, entry_size);
}