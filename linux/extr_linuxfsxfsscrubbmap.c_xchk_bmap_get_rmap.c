#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_rmap_irec {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; } ;
struct xchk_bmap_info {scalar_t__ whichfork; TYPE_2__* sc; scalar_t__ is_shared; } ;
struct TYPE_4__ {int /*<<< orphan*/  rmap_cur; } ;
struct TYPE_5__ {TYPE_1__ sa; } ;

/* Variables and functions */
 scalar_t__ XFS_ATTR_FORK ; 
 scalar_t__ XFS_COW_FORK ; 
 unsigned int XFS_RMAP_ATTR_FORK ; 
 int /*<<< orphan*/  xchk_fblock_xref_set_corrupt (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xchk_should_check_xref (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int xfs_rmap_get_rec (int /*<<< orphan*/ ,struct xfs_rmap_irec*,int*) ; 
 int xfs_rmap_lookup_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,int*) ; 
 int xfs_rmap_lookup_le_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,struct xfs_rmap_irec*,int*) ; 

__attribute__((used)) static inline bool
xchk_bmap_get_rmap(
	struct xchk_bmap_info	*info,
	struct xfs_bmbt_irec	*irec,
	xfs_agblock_t		agbno,
	uint64_t		owner,
	struct xfs_rmap_irec	*rmap)
{
	xfs_fileoff_t		offset;
	unsigned int		rflags = 0;
	int			has_rmap;
	int			error;

	if (info->whichfork == XFS_ATTR_FORK)
		rflags |= XFS_RMAP_ATTR_FORK;

	/*
	 * CoW staging extents are owned (on disk) by the refcountbt, so
	 * their rmaps do not have offsets.
	 */
	if (info->whichfork == XFS_COW_FORK)
		offset = 0;
	else
		offset = irec->br_startoff;

	/*
	 * If the caller thinks this could be a shared bmbt extent (IOWs,
	 * any data fork extent of a reflink inode) then we have to use the
	 * range rmap lookup to make sure we get the correct owner/offset.
	 */
	if (info->is_shared) {
		error = xfs_rmap_lookup_le_range(info->sc->sa.rmap_cur, agbno,
				owner, offset, rflags, rmap, &has_rmap);
		if (!xchk_should_check_xref(info->sc, &error,
				&info->sc->sa.rmap_cur))
			return false;
		goto out;
	}

	/*
	 * Otherwise, use the (faster) regular lookup.
	 */
	error = xfs_rmap_lookup_le(info->sc->sa.rmap_cur, agbno, 0, owner,
			offset, rflags, &has_rmap);
	if (!xchk_should_check_xref(info->sc, &error,
			&info->sc->sa.rmap_cur))
		return false;
	if (!has_rmap)
		goto out;

	error = xfs_rmap_get_rec(info->sc->sa.rmap_cur, rmap, &has_rmap);
	if (!xchk_should_check_xref(info->sc, &error,
			&info->sc->sa.rmap_cur))
		return false;

out:
	if (!has_rmap)
		xchk_fblock_xref_set_corrupt(info->sc, info->whichfork,
			irec->br_startoff);
	return has_rmap;
}