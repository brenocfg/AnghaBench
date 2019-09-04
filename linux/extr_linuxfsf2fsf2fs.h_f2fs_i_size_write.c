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
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FI_AUTO_RECOVER ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void f2fs_i_size_write(struct inode *inode, loff_t i_size)
{
	bool clean = !is_inode_flag_set(inode, FI_DIRTY_INODE);
	bool recover = is_inode_flag_set(inode, FI_AUTO_RECOVER);

	if (i_size_read(inode) == i_size)
		return;

	i_size_write(inode, i_size);
	f2fs_mark_inode_dirty_sync(inode, true);
	if (clean || recover)
		set_inode_flag(inode, FI_AUTO_RECOVER);
}