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
typedef  scalar_t__ xfs_agblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  agf_bp; int /*<<< orphan*/  refc_cur; } ;
struct xfs_scrub {TYPE_1__ sa; } ;
struct xfs_agf {int /*<<< orphan*/  agf_refcount_blocks; } ;

/* Variables and functions */
 struct xfs_agf* XFS_BUF_TO_AGF (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_block_xref_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_should_check_xref (struct xfs_scrub*,int*,int /*<<< orphan*/ *) ; 
 int xfs_btree_count_blocks (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline void
xchk_agf_xref_refcblks(
	struct xfs_scrub	*sc)
{
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(sc->sa.agf_bp);
	xfs_agblock_t		blocks;
	int			error;

	if (!sc->sa.refc_cur)
		return;

	error = xfs_btree_count_blocks(sc->sa.refc_cur, &blocks);
	if (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		return;
	if (blocks != be32_to_cpu(agf->agf_refcount_blocks))
		xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
}