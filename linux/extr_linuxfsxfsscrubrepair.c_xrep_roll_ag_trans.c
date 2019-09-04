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
struct TYPE_2__ {scalar_t__ agfl_bp; scalar_t__ agf_bp; scalar_t__ agi_bp; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_trans_bhold (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_bhold_release (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_bjoin (int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_trans_roll (int /*<<< orphan*/ *) ; 

int
xrep_roll_ag_trans(
	struct xfs_scrub	*sc)
{
	int			error;

	/* Keep the AG header buffers locked so we can keep going. */
	if (sc->sa.agi_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agi_bp);
	if (sc->sa.agf_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agf_bp);
	if (sc->sa.agfl_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agfl_bp);

	/* Roll the transaction. */
	error = xfs_trans_roll(&sc->tp);
	if (error)
		goto out_release;

	/* Join AG headers to the new transaction. */
	if (sc->sa.agi_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agi_bp);
	if (sc->sa.agf_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agf_bp);
	if (sc->sa.agfl_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agfl_bp);

	return 0;

out_release:
	/*
	 * Rolling failed, so release the hold on the buffers.  The
	 * buffers will be released during teardown on our way out
	 * of the kernel.
	 */
	if (sc->sa.agi_bp)
		xfs_trans_bhold_release(sc->tp, sc->sa.agi_bp);
	if (sc->sa.agf_bp)
		xfs_trans_bhold_release(sc->tp, sc->sa.agf_bp);
	if (sc->sa.agfl_bp)
		xfs_trans_bhold_release(sc->tp, sc->sa.agfl_bp);

	return error;
}