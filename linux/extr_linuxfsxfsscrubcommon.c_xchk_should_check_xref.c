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
struct xfs_scrub {TYPE_1__* sm; } ;
struct xfs_btree_cur {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_ERROR ; 
 int /*<<< orphan*/  XFS_SCRUB_OFLAG_XFAIL ; 
 int /*<<< orphan*/  __return_address ; 
 int /*<<< orphan*/  trace_xchk_xref_error (struct xfs_scrub*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xchk_skip_xref (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 

bool
xchk_should_check_xref(
	struct xfs_scrub	*sc,
	int			*error,
	struct xfs_btree_cur	**curpp)
{
	/* No point in xref if we already know we're corrupt. */
	if (xchk_skip_xref(sc->sm))
		return false;

	if (*error == 0)
		return true;

	if (curpp) {
		/* If we've already given up on xref, just bail out. */
		if (!*curpp)
			return false;

		/* xref error, delete cursor and bail out. */
		xfs_btree_del_cursor(*curpp, XFS_BTREE_ERROR);
		*curpp = NULL;
	}

	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XFAIL;
	trace_xchk_xref_error(sc, *error, __return_address);

	/*
	 * Errors encountered during cross-referencing with another
	 * data structure should not cause this scrubber to abort.
	 */
	*error = 0;
	return false;
}