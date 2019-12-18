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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_version; } ;
struct ext4_inode_info {unsigned long i_flags; int /*<<< orphan*/  i_disksize; int /*<<< orphan*/  i_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 unsigned long EXT4_FL_SHOULD_SWAP ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT_MAX_BLOCKS ; 
 int /*<<< orphan*/  ext4_es_remove_extent (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memswap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swap_inode_data(struct inode *inode1, struct inode *inode2)
{
	loff_t isize;
	struct ext4_inode_info *ei1;
	struct ext4_inode_info *ei2;
	unsigned long tmp;

	ei1 = EXT4_I(inode1);
	ei2 = EXT4_I(inode2);

	swap(inode1->i_version, inode2->i_version);
	swap(inode1->i_atime, inode2->i_atime);
	swap(inode1->i_mtime, inode2->i_mtime);

	memswap(ei1->i_data, ei2->i_data, sizeof(ei1->i_data));
	tmp = ei1->i_flags & EXT4_FL_SHOULD_SWAP;
	ei1->i_flags = (ei2->i_flags & EXT4_FL_SHOULD_SWAP) |
		(ei1->i_flags & ~EXT4_FL_SHOULD_SWAP);
	ei2->i_flags = tmp | (ei2->i_flags & ~EXT4_FL_SHOULD_SWAP);
	swap(ei1->i_disksize, ei2->i_disksize);
	ext4_es_remove_extent(inode1, 0, EXT_MAX_BLOCKS);
	ext4_es_remove_extent(inode2, 0, EXT_MAX_BLOCKS);

	isize = i_size_read(inode1);
	i_size_write(inode1, i_size_read(inode2));
	i_size_write(inode2, isize);
}