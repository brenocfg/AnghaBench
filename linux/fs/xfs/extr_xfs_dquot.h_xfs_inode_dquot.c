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
typedef  int /*<<< orphan*/  xfs_dquot_t ;
struct xfs_inode {int /*<<< orphan*/ * i_pdquot; int /*<<< orphan*/ * i_gdquot; int /*<<< orphan*/ * i_udquot; } ;

/* Variables and functions */
 int XFS_DQ_ALLTYPES ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 

__attribute__((used)) static inline xfs_dquot_t *xfs_inode_dquot(struct xfs_inode *ip, int type)
{
	switch (type & XFS_DQ_ALLTYPES) {
	case XFS_DQ_USER:
		return ip->i_udquot;
	case XFS_DQ_GROUP:
		return ip->i_gdquot;
	case XFS_DQ_PROJ:
		return ip->i_pdquot;
	default:
		return NULL;
	}
}