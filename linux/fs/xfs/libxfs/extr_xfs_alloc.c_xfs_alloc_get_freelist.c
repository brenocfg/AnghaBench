#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
struct TYPE_13__ {int /*<<< orphan*/  pagf_btreeblks; int /*<<< orphan*/  pagf_flcount; int /*<<< orphan*/  pagf_agflreset; } ;
typedef  TYPE_2__ xfs_perag_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
struct TYPE_14__ {scalar_t__ agf_btreeblks; scalar_t__ agf_flcount; scalar_t__ agf_seqno; scalar_t__ agf_flfirst; } ;
typedef  TYPE_3__ xfs_agf_t ;
typedef  size_t xfs_agblock_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t NULLAGBLOCK ; 
 int XFS_AGF_BTREEBLKS ; 
 int XFS_AGF_FLCOUNT ; 
 int XFS_AGF_FLFIRST ; 
 TYPE_3__* XFS_BUF_TO_AGF (int /*<<< orphan*/ *) ; 
 scalar_t__* XFS_BUF_TO_AGFL_BNO (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_add_cpu (scalar_t__*,int) ; 
 size_t be32_to_cpu (scalar_t__) ; 
 size_t xfs_agfl_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_alloc_log_agf (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int xfs_alloc_read_agfl (int /*<<< orphan*/ *,TYPE_1__*,size_t,int /*<<< orphan*/ **) ; 
 TYPE_2__* xfs_perag_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  xfs_perag_put (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_trans_agflist_delta (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xfs_trans_brelse (TYPE_1__*,int /*<<< orphan*/ *) ; 

int				/* error */
xfs_alloc_get_freelist(
	xfs_trans_t	*tp,	/* transaction pointer */
	xfs_buf_t	*agbp,	/* buffer containing the agf structure */
	xfs_agblock_t	*bnop,	/* block address retrieved from freelist */
	int		btreeblk) /* destination is a AGF btree */
{
	xfs_agf_t	*agf;	/* a.g. freespace structure */
	xfs_buf_t	*agflbp;/* buffer for a.g. freelist structure */
	xfs_agblock_t	bno;	/* block number returned */
	__be32		*agfl_bno;
	int		error;
	int		logflags;
	xfs_mount_t	*mp = tp->t_mountp;
	xfs_perag_t	*pag;	/* per allocation group data */

	/*
	 * Freelist is empty, give up.
	 */
	agf = XFS_BUF_TO_AGF(agbp);
	if (!agf->agf_flcount) {
		*bnop = NULLAGBLOCK;
		return 0;
	}
	/*
	 * Read the array of free blocks.
	 */
	error = xfs_alloc_read_agfl(mp, tp, be32_to_cpu(agf->agf_seqno),
				    &agflbp);
	if (error)
		return error;


	/*
	 * Get the block number and update the data structures.
	 */
	agfl_bno = XFS_BUF_TO_AGFL_BNO(mp, agflbp);
	bno = be32_to_cpu(agfl_bno[be32_to_cpu(agf->agf_flfirst)]);
	be32_add_cpu(&agf->agf_flfirst, 1);
	xfs_trans_brelse(tp, agflbp);
	if (be32_to_cpu(agf->agf_flfirst) == xfs_agfl_size(mp))
		agf->agf_flfirst = 0;

	pag = xfs_perag_get(mp, be32_to_cpu(agf->agf_seqno));
	ASSERT(!pag->pagf_agflreset);
	be32_add_cpu(&agf->agf_flcount, -1);
	xfs_trans_agflist_delta(tp, -1);
	pag->pagf_flcount--;

	logflags = XFS_AGF_FLFIRST | XFS_AGF_FLCOUNT;
	if (btreeblk) {
		be32_add_cpu(&agf->agf_btreeblks, 1);
		pag->pagf_btreeblks++;
		logflags |= XFS_AGF_BTREEBLKS;
	}
	xfs_perag_put(pag);

	xfs_alloc_log_agf(tp, agbp, logflags);
	*bnop = bno;

	return 0;
}