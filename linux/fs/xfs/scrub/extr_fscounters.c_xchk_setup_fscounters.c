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
struct xfs_scrub {int /*<<< orphan*/  mp; struct xchk_fscounters* buf; } ;
struct xfs_inode {int dummy; } ;
struct xchk_fscounters {int /*<<< orphan*/  icount_max; int /*<<< orphan*/  icount_min; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct xchk_fscounters* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int xchk_fscount_warmup (struct xfs_scrub*) ; 
 int /*<<< orphan*/  xchk_stop_reaping (struct xfs_scrub*) ; 
 int xchk_trans_alloc (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_icount_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xchk_setup_fscounters(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	struct xchk_fscounters	*fsc;
	int			error;

	sc->buf = kmem_zalloc(sizeof(struct xchk_fscounters), 0);
	if (!sc->buf)
		return -ENOMEM;
	fsc = sc->buf;

	xfs_icount_range(sc->mp, &fsc->icount_min, &fsc->icount_max);

	/* We must get the incore counters set up before we can proceed. */
	error = xchk_fscount_warmup(sc);
	if (error)
		return error;

	/*
	 * Pause background reclaim while we're scrubbing to reduce the
	 * likelihood of background perturbations to the counters throwing off
	 * our calculations.
	 */
	xchk_stop_reaping(sc);

	return xchk_trans_alloc(sc, 0);
}