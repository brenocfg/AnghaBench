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
typedef  scalar_t__ xfs_agino_t ;
struct TYPE_2__ {int /*<<< orphan*/  agi_bp; int /*<<< orphan*/  ino_cur; } ;
struct xfs_scrub {TYPE_1__ sa; } ;
struct xfs_agi {int /*<<< orphan*/  agi_freecount; int /*<<< orphan*/  agi_count; } ;

/* Variables and functions */
 struct xfs_agi* XFS_BUF_TO_AGI (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_block_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 int xfs_ialloc_count_inodes (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static inline void
xchk_agi_xref_icounts(
	struct xfs_scrub	*sc)
{
	struct xfs_agi		*agi = XFS_BUF_TO_AGI(sc->sa.agi_bp);
	xfs_agino_t		icount;
	xfs_agino_t		freecount;
	int			error;

	if (!sc->sa.ino_cur)
		return;

	error = xfs_ialloc_count_inodes(sc->sa.ino_cur, &icount, &freecount);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.ino_cur))
		return;
	if (be32_to_cpu(agi->agi_count) != icount ||
	    be32_to_cpu(agi->agi_freecount) != freecount)
		xchk_block_xref_set_corrupt(sc, sc->sa.agi_bp);
}