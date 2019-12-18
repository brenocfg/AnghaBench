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
struct xfs_mount {int dummy; } ;
struct xfs_inode_log_item {int /*<<< orphan*/  ili_item; struct xfs_inode* ili_inode; } ;
struct xfs_inode {struct xfs_inode_log_item* i_itemp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_LI_INODE ; 
 struct xfs_inode_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ili_zone ; 
 int /*<<< orphan*/  xfs_inode_item_ops ; 
 int /*<<< orphan*/  xfs_log_item_init (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_inode_item_init(
	struct xfs_inode	*ip,
	struct xfs_mount	*mp)
{
	struct xfs_inode_log_item *iip;

	ASSERT(ip->i_itemp == NULL);
	iip = ip->i_itemp = kmem_zone_zalloc(xfs_ili_zone, 0);

	iip->ili_inode = ip;
	xfs_log_item_init(mp, &iip->ili_item, XFS_LI_INODE,
						&xfs_inode_item_ops);
}