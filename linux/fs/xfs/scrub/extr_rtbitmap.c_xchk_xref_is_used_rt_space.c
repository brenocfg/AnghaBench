#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_rtblock_t ;
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_scrub {TYPE_2__* mp; int /*<<< orphan*/  tp; int /*<<< orphan*/  sm; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb_rextsize; } ;
struct TYPE_6__ {TYPE_3__* m_rbmip; TYPE_1__ m_sb; } ;

/* Variables and functions */
 int XFS_ILOCK_RTBITMAP ; 
 int XFS_ILOCK_SHARED ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_ino_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ xchk_skip_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_3__*,int) ; 
 int xfs_rtalloc_extent_is_free (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*) ; 

void
xchk_xref_is_used_rt_space(
	struct xfs_scrub	*sc,
	xfs_rtblock_t		fsbno,
	xfs_extlen_t		len)
{
	xfs_rtblock_t		startext;
	xfs_rtblock_t		endext;
	xfs_rtblock_t		extcount;
	bool			is_free;
	int			error;

	if (xchk_skip_xref(sc->sm))
		return;

	startext = fsbno;
	endext = fsbno + len - 1;
	do_div(startext, sc->mp->m_sb.sb_rextsize);
	do_div(endext, sc->mp->m_sb.sb_rextsize);
	extcount = endext - startext + 1;
	xfs_ilock(sc->mp->m_rbmip, XFS_ILOCK_SHARED | XFS_ILOCK_RTBITMAP);
	error = xfs_rtalloc_extent_is_free(sc->mp, sc->tp, startext, extcount,
			&is_free);
	if (!xchk_should_check_xref(sc, &error, NULL))
		goto out_unlock;
	if (is_free)
		xchk_ino_xref_set_corrupt(sc, sc->mp->m_rbmip->i_ino);
out_unlock:
	xfs_iunlock(sc->mp->m_rbmip, XFS_ILOCK_SHARED | XFS_ILOCK_RTBITMAP);
}