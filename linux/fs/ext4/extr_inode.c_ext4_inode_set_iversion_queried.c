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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 int EXT4_EA_INODE_FL ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  inode_set_iversion_queried (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_iversion_raw (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void ext4_inode_set_iversion_queried(struct inode *inode, u64 val)
{
	if (unlikely(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL))
		inode_set_iversion_raw(inode, val);
	else
		inode_set_iversion_queried(inode, val);
}