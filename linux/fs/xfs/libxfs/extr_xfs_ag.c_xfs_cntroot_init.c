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
struct xfs_buf {int dummy; } ;
struct aghdr_init_data {int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTNUM_CNT ; 
 int /*<<< orphan*/  xfs_btree_init_block (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_freesp_init_recs (struct xfs_mount*,struct xfs_buf*,struct aghdr_init_data*) ; 

__attribute__((used)) static void
xfs_cntroot_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	xfs_btree_init_block(mp, bp, XFS_BTNUM_CNT, 0, 1, id->agno);
	xfs_freesp_init_recs(mp, bp, id);
}