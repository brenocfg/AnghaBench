#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xfs_scrub {TYPE_1__* sm; } ;
struct TYPE_7__ {int /*<<< orphan*/  geo; int /*<<< orphan*/  whichfork; } ;
struct xchk_da_btree {TYPE_5__* state; TYPE_2__ dargs; struct xfs_scrub* sc; } ;
struct TYPE_9__ {TYPE_3__* blk; } ;
struct TYPE_10__ {TYPE_4__ path; } ;
struct TYPE_8__ {int /*<<< orphan*/  blkno; } ;
struct TYPE_6__ {int /*<<< orphan*/  sm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SCRUB_OFLAG_CORRUPT ; 
 int /*<<< orphan*/  __return_address ; 
 int /*<<< orphan*/  trace_xchk_fblock_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_da_to_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xchk_da_set_corrupt(
	struct xchk_da_btree	*ds,
	int			level)
{
	struct xfs_scrub	*sc = ds->sc;

	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;

	trace_xchk_fblock_error(sc, ds->dargs.whichfork,
			xfs_dir2_da_to_db(ds->dargs.geo,
				ds->state->path.blk[level].blkno),
			__return_address);
}