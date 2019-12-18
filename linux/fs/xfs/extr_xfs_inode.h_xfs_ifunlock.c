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
struct xfs_inode {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IFLOCK ; 
 int /*<<< orphan*/  __XFS_IFLOCK_BIT ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iflags_clear (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_isiflocked (struct xfs_inode*) ; 

__attribute__((used)) static inline void xfs_ifunlock(struct xfs_inode *ip)
{
	ASSERT(xfs_isiflocked(ip));
	xfs_iflags_clear(ip, XFS_IFLOCK);
	smp_mb();
	wake_up_bit(&ip->i_flags, __XFS_IFLOCK_BIT);
}