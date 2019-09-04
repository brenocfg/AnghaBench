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
typedef  scalar_t__ xfs_dablk_t ;
struct xfs_da_args {TYPE_1__* geo; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsbcount; scalar_t__ leafblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_xfs_da_grow_inode (struct xfs_da_args*) ; 
 int xfs_da_grow_inode_int (struct xfs_da_args*,scalar_t__*,int /*<<< orphan*/ ) ; 

int
xfs_da_grow_inode(
	struct xfs_da_args	*args,
	xfs_dablk_t		*new_blkno)
{
	xfs_fileoff_t		bno;
	int			error;

	trace_xfs_da_grow_inode(args);

	bno = args->geo->leafblk;
	error = xfs_da_grow_inode_int(args, &bno, args->geo->fsbcount);
	if (!error)
		*new_blkno = (xfs_dablk_t)bno;
	return error;
}