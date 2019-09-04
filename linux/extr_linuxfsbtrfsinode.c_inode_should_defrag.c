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
struct btrfs_inode {scalar_t__ disk_i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_add_inode_defrag (int /*<<< orphan*/ *,struct btrfs_inode*) ; 

__attribute__((used)) static inline void inode_should_defrag(struct btrfs_inode *inode,
		u64 start, u64 end, u64 num_bytes, u64 small_write)
{
	/* If this is a small write inside eof, kick off a defrag */
	if (num_bytes < small_write &&
	    (start > 0 || end + 1 < inode->disk_i_size))
		btrfs_add_inode_defrag(NULL, inode);
}