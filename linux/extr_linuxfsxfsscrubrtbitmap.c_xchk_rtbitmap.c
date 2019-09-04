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
struct xfs_scrub {int /*<<< orphan*/  tp; TYPE_1__* sm; } ;
struct TYPE_2__ {int sm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 int /*<<< orphan*/  xchk_fblock_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int xchk_metadata_inode_forks (struct xfs_scrub*) ; 
 int /*<<< orphan*/  xchk_rtbitmap_rec ; 
 int xfs_rtalloc_query_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_scrub*) ; 

int
xchk_rtbitmap(
	struct xfs_scrub	*sc)
{
	int			error;

	/* Invoke the fork scrubber. */
	error = xchk_metadata_inode_forks(sc);
	if (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		return error;

	error = xfs_rtalloc_query_all(sc->tp, xchk_rtbitmap_rec, sc);
	if (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		goto out;

out:
	return error;
}