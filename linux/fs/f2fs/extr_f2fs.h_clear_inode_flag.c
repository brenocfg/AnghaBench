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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  __mark_inode_dirty_flag (struct inode*,int,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_inode_flag(struct inode *inode, int flag)
{
	if (test_bit(flag, &F2FS_I(inode)->flags))
		clear_bit(flag, &F2FS_I(inode)->flags);
	__mark_inode_dirty_flag(inode, flag, false);
}