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
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_irele (struct xfs_inode*,int /*<<< orphan*/ ) ; 

void
xfs_irele(
	struct xfs_inode	*ip)
{
	trace_xfs_irele(ip, _RET_IP_);
	iput(VFS_I(ip));
}