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
struct TYPE_2__ {int di_flags; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
typedef  int /*<<< orphan*/  prid_t ;

/* Variables and functions */
 int XFS_DIFLAG_PROJINHERIT ; 
 int /*<<< orphan*/  XFS_PROJID_DEFAULT ; 
 int /*<<< orphan*/  xfs_get_projid (struct xfs_inode*) ; 

__attribute__((used)) static inline prid_t
xfs_get_initial_prid(struct xfs_inode *dp)
{
	if (dp->i_d.di_flags & XFS_DIFLAG_PROJINHERIT)
		return xfs_get_projid(dp);

	return XFS_PROJID_DEFAULT;
}