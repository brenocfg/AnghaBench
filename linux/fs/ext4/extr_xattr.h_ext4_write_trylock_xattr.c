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
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_NO_EXPAND ; 
 scalar_t__ down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ext4_write_trylock_xattr(struct inode *inode, int *save)
{
	if (down_write_trylock(&EXT4_I(inode)->xattr_sem) == 0)
		return 0;
	*save = ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND);
	ext4_set_inode_state(inode, EXT4_STATE_NO_EXPAND);
	return 1;
}