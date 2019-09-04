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
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_truncate (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ext4_truncate_failed_write(struct inode *inode)
{
	/*
	 * We don't need to call ext4_break_layouts() because the blocks we
	 * are truncating were never visible to userspace.
	 */
	down_write(&EXT4_I(inode)->i_mmap_sem);
	truncate_inode_pages(inode->i_mapping, inode->i_size);
	ext4_truncate(inode);
	up_write(&EXT4_I(inode)->i_mmap_sem);
}