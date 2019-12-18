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
struct TYPE_2__ {int di_flags2; } ;
struct xfs_inode {TYPE_1__ i_d; } ;

/* Variables and functions */
 int XFS_DIFLAG2_REFLINK ; 

__attribute__((used)) static inline bool xfs_is_reflink_inode(struct xfs_inode *ip)
{
	return ip->i_d.di_flags2 & XFS_DIFLAG2_REFLINK;
}