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
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;

/* Variables and functions */
 int xfs_alloc_read_agf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int					/* error */
xfs_alloc_pagf_init(
	xfs_mount_t		*mp,	/* file system mount structure */
	xfs_trans_t		*tp,	/* transaction pointer */
	xfs_agnumber_t		agno,	/* allocation group number */
	int			flags)	/* XFS_ALLOC_FLAGS_... */
{
	xfs_buf_t		*bp;
	int			error;

	if ((error = xfs_alloc_read_agf(mp, tp, agno, flags, &bp)))
		return error;
	if (bp)
		xfs_trans_brelse(tp, bp);
	return 0;
}