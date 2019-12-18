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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_scrub {TYPE_1__* sm; } ;
struct TYPE_2__ {int /*<<< orphan*/  sm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SCRUB_OFLAG_WARNING ; 
 int /*<<< orphan*/  __return_address ; 
 int /*<<< orphan*/  trace_xchk_fblock_warning (struct xfs_scrub*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xchk_fblock_set_warning(
	struct xfs_scrub	*sc,
	int			whichfork,
	xfs_fileoff_t		offset)
{
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_WARNING;
	trace_xchk_fblock_warning(sc, whichfork, offset, __return_address);
}