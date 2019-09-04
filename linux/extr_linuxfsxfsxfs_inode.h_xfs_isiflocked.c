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
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_IFLOCK ; 
 int xfs_iflags_test (struct xfs_inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xfs_isiflocked(struct xfs_inode *ip)
{
	return xfs_iflags_test(ip, XFS_IFLOCK);
}