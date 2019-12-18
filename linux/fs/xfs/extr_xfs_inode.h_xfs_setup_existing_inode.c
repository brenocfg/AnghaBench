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
 int /*<<< orphan*/  xfs_finish_inode_setup (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_setup_inode (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_setup_iops (struct xfs_inode*) ; 

__attribute__((used)) static inline void xfs_setup_existing_inode(struct xfs_inode *ip)
{
	xfs_setup_inode(ip);
	xfs_setup_iops(ip);
	xfs_finish_inode_setup(ip);
}