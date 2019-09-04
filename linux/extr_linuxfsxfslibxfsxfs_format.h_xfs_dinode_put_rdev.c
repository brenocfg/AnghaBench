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
typedef  int /*<<< orphan*/  xfs_dev_t ;
struct xfs_dinode {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ XFS_DFORK_DPTR (struct xfs_dinode*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xfs_dinode_put_rdev(struct xfs_dinode *dip, xfs_dev_t rdev)
{
	*(__be32 *)XFS_DFORK_DPTR(dip) = cpu_to_be32(rdev);
}