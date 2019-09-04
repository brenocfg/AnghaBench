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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct xfs_perag {int pagi_init; scalar_t__ pagi_freecount; scalar_t__ pagi_count; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agi {int /*<<< orphan*/  agi_freecount; int /*<<< orphan*/  agi_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct xfs_agi* XFS_BUF_TO_AGI (struct xfs_buf*) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_ialloc_read_agi (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int xfs_read_agi (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,struct xfs_buf**) ; 

int
xfs_ialloc_read_agi(
	struct xfs_mount	*mp,	/* file system mount structure */
	struct xfs_trans	*tp,	/* transaction pointer */
	xfs_agnumber_t		agno,	/* allocation group number */
	struct xfs_buf		**bpp)	/* allocation group hdr buf */
{
	struct xfs_agi		*agi;	/* allocation group header */
	struct xfs_perag	*pag;	/* per allocation group data */
	int			error;

	trace_xfs_ialloc_read_agi(mp, agno);

	error = xfs_read_agi(mp, tp, agno, bpp);
	if (error)
		return error;

	agi = XFS_BUF_TO_AGI(*bpp);
	pag = xfs_perag_get(mp, agno);
	if (!pag->pagi_init) {
		pag->pagi_freecount = be32_to_cpu(agi->agi_freecount);
		pag->pagi_count = be32_to_cpu(agi->agi_count);
		pag->pagi_init = 1;
	}

	/*
	 * It's possible for these to be out of sync if
	 * we are in the middle of a forced shutdown.
	 */
	ASSERT(pag->pagi_freecount == be32_to_cpu(agi->agi_freecount) ||
		XFS_FORCED_SHUTDOWN(mp));
	xfs_perag_put(pag);
	return 0;
}