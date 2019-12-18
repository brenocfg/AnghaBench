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
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_da_args {TYPE_1__* geo; int /*<<< orphan*/  dp; } ;
struct TYPE_2__ {scalar_t__ leafblk; scalar_t__ fsbcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int xfs_bmap_last_offset (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

int
xfs_dir2_isleaf(
	struct xfs_da_args	*args,
	int			*vp)	/* out: 1 is block, 0 is not block */
{
	xfs_fileoff_t		last;	/* last file offset */
	int			rval;

	if ((rval = xfs_bmap_last_offset(args->dp, &last, XFS_DATA_FORK)))
		return rval;
	*vp = last == args->geo->leafblk + args->geo->fsbcount;
	return 0;
}