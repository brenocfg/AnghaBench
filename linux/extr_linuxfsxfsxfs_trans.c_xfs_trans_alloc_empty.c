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
struct xfs_trans_res {int /*<<< orphan*/  member_0; } ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_TRANS_NO_WRITECOUNT ; 
 int xfs_trans_alloc (struct xfs_mount*,struct xfs_trans_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 

int
xfs_trans_alloc_empty(
	struct xfs_mount		*mp,
	struct xfs_trans		**tpp)
{
	struct xfs_trans_res		resv = {0};

	return xfs_trans_alloc(mp, &resv, 0, 0, XFS_TRANS_NO_WRITECOUNT, tpp);
}