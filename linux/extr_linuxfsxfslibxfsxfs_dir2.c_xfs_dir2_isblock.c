#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_da_args {TYPE_2__* geo; TYPE_3__* dp; } ;
struct TYPE_4__ {scalar_t__ di_size; } ;
struct TYPE_6__ {TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
struct TYPE_5__ {scalar_t__ blksize; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_FSB_TO_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_bmap_last_offset (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_dir2_isblock(
	struct xfs_da_args	*args,
	int			*vp)	/* out: 1 is block, 0 is not block */
{
	xfs_fileoff_t		last;	/* last file offset */
	int			rval;

	if ((rval = xfs_bmap_last_offset(args->dp, &last, XFS_DATA_FORK)))
		return rval;
	rval = XFS_FSB_TO_B(args->dp->i_mount, last) == args->geo->blksize;
	if (rval != 0 && args->dp->i_d.di_size != args->geo->blksize)
		return -EFSCORRUPTED;
	*vp = rval;
	return 0;
}