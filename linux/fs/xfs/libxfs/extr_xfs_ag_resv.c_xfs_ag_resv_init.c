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
typedef  scalar_t__ xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_5__ {scalar_t__ ar_asked; } ;
struct TYPE_4__ {scalar_t__ ar_asked; } ;
struct xfs_perag {scalar_t__ pagf_freeblks; scalar_t__ pagf_flcount; int /*<<< orphan*/  pag_agno; struct xfs_mount* pag_mount; TYPE_2__ pag_rmapbt_resv; TYPE_1__ pag_meta_resv; } ;
struct xfs_mount {int m_finobt_nores; } ;
struct TYPE_6__ {scalar_t__ ar_reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_AG_RESV_METADATA ; 
 int /*<<< orphan*/  XFS_AG_RESV_RMAPBT ; 
 int __xfs_ag_resv_init (struct xfs_perag*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int xfs_alloc_pagf_init (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_finobt_calc_reserves (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 TYPE_3__* xfs_perag_resv (struct xfs_perag*,int /*<<< orphan*/ ) ; 
 int xfs_refcountbt_calc_reserves (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int xfs_rmapbt_calc_reserves (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int
xfs_ag_resv_init(
	struct xfs_perag		*pag,
	struct xfs_trans		*tp)
{
	struct xfs_mount		*mp = pag->pag_mount;
	xfs_agnumber_t			agno = pag->pag_agno;
	xfs_extlen_t			ask;
	xfs_extlen_t			used;
	int				error = 0;

	/* Create the metadata reservation. */
	if (pag->pag_meta_resv.ar_asked == 0) {
		ask = used = 0;

		error = xfs_refcountbt_calc_reserves(mp, tp, agno, &ask, &used);
		if (error)
			goto out;

		error = xfs_finobt_calc_reserves(mp, tp, agno, &ask, &used);
		if (error)
			goto out;

		error = __xfs_ag_resv_init(pag, XFS_AG_RESV_METADATA,
				ask, used);
		if (error) {
			/*
			 * Because we didn't have per-AG reservations when the
			 * finobt feature was added we might not be able to
			 * reserve all needed blocks.  Warn and fall back to the
			 * old and potentially buggy code in that case, but
			 * ensure we do have the reservation for the refcountbt.
			 */
			ask = used = 0;

			mp->m_finobt_nores = true;

			error = xfs_refcountbt_calc_reserves(mp, tp, agno, &ask,
					&used);
			if (error)
				goto out;

			error = __xfs_ag_resv_init(pag, XFS_AG_RESV_METADATA,
					ask, used);
			if (error)
				goto out;
		}
	}

	/* Create the RMAPBT metadata reservation */
	if (pag->pag_rmapbt_resv.ar_asked == 0) {
		ask = used = 0;

		error = xfs_rmapbt_calc_reserves(mp, tp, agno, &ask, &used);
		if (error)
			goto out;

		error = __xfs_ag_resv_init(pag, XFS_AG_RESV_RMAPBT, ask, used);
		if (error)
			goto out;
	}

#ifdef DEBUG
	/* need to read in the AGF for the ASSERT below to work */
	error = xfs_alloc_pagf_init(pag->pag_mount, tp, pag->pag_agno, 0);
	if (error)
		return error;

	ASSERT(xfs_perag_resv(pag, XFS_AG_RESV_METADATA)->ar_reserved +
	       xfs_perag_resv(pag, XFS_AG_RESV_RMAPBT)->ar_reserved <=
	       pag->pagf_freeblks + pag->pagf_flcount);
#endif
out:
	return error;
}