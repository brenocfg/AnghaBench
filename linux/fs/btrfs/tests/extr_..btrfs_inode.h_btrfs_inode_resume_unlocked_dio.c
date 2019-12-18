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
struct btrfs_inode {int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_READDIO_NEED_LOCK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static inline void btrfs_inode_resume_unlocked_dio(struct btrfs_inode *inode)
{
	smp_mb__before_atomic();
	clear_bit(BTRFS_INODE_READDIO_NEED_LOCK, &inode->runtime_flags);
}