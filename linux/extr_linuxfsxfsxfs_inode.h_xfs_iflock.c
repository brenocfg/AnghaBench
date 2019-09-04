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
 int /*<<< orphan*/  __xfs_iflock (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iflock_nowait (struct xfs_inode*) ; 

__attribute__((used)) static inline void xfs_iflock(struct xfs_inode *ip)
{
	if (!xfs_iflock_nowait(ip))
		__xfs_iflock(ip);
}