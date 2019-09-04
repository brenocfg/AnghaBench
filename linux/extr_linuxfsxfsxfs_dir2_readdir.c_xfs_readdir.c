#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int dummy; } ;
struct TYPE_5__ {scalar_t__ di_format; } ;
struct xfs_inode {TYPE_1__ i_d; TYPE_2__* i_mount; } ;
struct xfs_da_args {struct xfs_trans* trans; int /*<<< orphan*/  geo; struct xfs_inode* dp; int /*<<< orphan*/ * member_0; } ;
struct dir_context {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  m_dir_geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_4__* VFS_I (struct xfs_inode*) ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (TYPE_2__*) ; 
 int /*<<< orphan*/  XFS_STATS_INC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_readdir (struct xfs_inode*) ; 
 int xfs_dir2_block_getdents (struct xfs_da_args*,struct dir_context*) ; 
 int xfs_dir2_isblock (struct xfs_da_args*,int*) ; 
 int xfs_dir2_leaf_getdents (struct xfs_da_args*,struct dir_context*,size_t) ; 
 int xfs_dir2_sf_getdents (struct xfs_da_args*,struct dir_context*) ; 
 int /*<<< orphan*/  xs_dir_getdents ; 

int
xfs_readdir(
	struct xfs_trans	*tp,
	struct xfs_inode	*dp,
	struct dir_context	*ctx,
	size_t			bufsize)
{
	struct xfs_da_args	args = { NULL };
	int			rval;
	int			v;

	trace_xfs_readdir(dp);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return -EIO;

	ASSERT(S_ISDIR(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_dir_getdents);

	args.dp = dp;
	args.geo = dp->i_mount->m_dir_geo;
	args.trans = tp;

	if (dp->i_d.di_format == XFS_DINODE_FMT_LOCAL)
		rval = xfs_dir2_sf_getdents(&args, ctx);
	else if ((rval = xfs_dir2_isblock(&args, &v)))
		;
	else if (v)
		rval = xfs_dir2_block_getdents(&args, ctx);
	else
		rval = xfs_dir2_leaf_getdents(&args, ctx, bufsize);

	return rval;
}