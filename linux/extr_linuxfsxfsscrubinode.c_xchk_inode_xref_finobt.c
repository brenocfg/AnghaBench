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
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  scalar_t__ xfs_agino_t ;
struct TYPE_2__ {int /*<<< orphan*/  fino_cur; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  mp; int /*<<< orphan*/  sm; } ;
struct xfs_inobt_rec_incore {scalar_t__ ir_startino; int ir_free; } ;

/* Variables and functions */
 int XFS_INOBT_MASK (scalar_t__) ; 
 scalar_t__ XFS_INODES_PER_CHUNK ; 
 scalar_t__ XFS_INO_TO_AGINO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_LOOKUP_LE ; 
 int /*<<< orphan*/  xchk_btree_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ xchk_skip_xref (int /*<<< orphan*/ ) ; 
 int xfs_inobt_get_rec (int /*<<< orphan*/ ,struct xfs_inobt_rec_incore*,int*) ; 
 int xfs_inobt_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
xchk_inode_xref_finobt(
	struct xfs_scrub		*sc,
	xfs_ino_t			ino)
{
	struct xfs_inobt_rec_incore	rec;
	xfs_agino_t			agino;
	int				has_record;
	int				error;

	if (!sc->sa.fino_cur || xchk_skip_xref(sc->sm))
		return;

	agino = XFS_INO_TO_AGINO(sc->mp, ino);

	/*
	 * Try to get the finobt record.  If we can't get it, then we're
	 * in good shape.
	 */
	error = xfs_inobt_lookup(sc->sa.fino_cur, agino, XFS_LOOKUP_LE,
			&has_record);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.fino_cur) ||
	    !has_record)
		return;

	error = xfs_inobt_get_rec(sc->sa.fino_cur, &rec, &has_record);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.fino_cur) ||
	    !has_record)
		return;

	/*
	 * Otherwise, make sure this record either doesn't cover this inode,
	 * or that it does but it's marked present.
	 */
	if (rec.ir_startino > agino ||
	    rec.ir_startino + XFS_INODES_PER_CHUNK <= agino)
		return;

	if (rec.ir_free & XFS_INOBT_MASK(agino - rec.ir_startino))
		xchk_btree_xref_set_corrupt(sc, sc->sa.fino_cur, 0);
}