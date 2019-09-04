#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_trans {TYPE_2__* t_mountp; } ;
struct xfs_buf {int dummy; } ;
struct xfs_alloc_arg {scalar_t__ agno; int /*<<< orphan*/  pag; struct xfs_buf* agbp; TYPE_2__* mp; struct xfs_trans* tp; } ;
struct TYPE_3__ {scalar_t__ sb_agcount; } ;
struct TYPE_4__ {TYPE_1__ m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_ALLOC_FLAG_FREEING ; 
 int /*<<< orphan*/  memset (struct xfs_alloc_arg*,int /*<<< orphan*/ ,int) ; 
 int xfs_alloc_fix_freelist (struct xfs_alloc_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_get (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (int /*<<< orphan*/ ) ; 

int
xfs_free_extent_fix_freelist(
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	struct xfs_buf		**agbp)
{
	struct xfs_alloc_arg	args;
	int			error;

	memset(&args, 0, sizeof(struct xfs_alloc_arg));
	args.tp = tp;
	args.mp = tp->t_mountp;
	args.agno = agno;

	/*
	 * validate that the block number is legal - the enables us to detect
	 * and handle a silent filesystem corruption rather than crashing.
	 */
	if (args.agno >= args.mp->m_sb.sb_agcount)
		return -EFSCORRUPTED;

	args.pag = xfs_perag_get(args.mp, args.agno);
	ASSERT(args.pag);

	error = xfs_alloc_fix_freelist(&args, XFS_ALLOC_FLAG_FREEING);
	if (error)
		goto out;

	*agbp = args.agbp;
out:
	xfs_perag_put(args.pag);
	return error;
}