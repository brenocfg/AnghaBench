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
struct xfs_perag {unsigned int pag_sick; unsigned int pag_checked; int /*<<< orphan*/  pag_state_lock; int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int XFS_SICK_AG_PRIMARY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_ag_mark_sick (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void
xfs_ag_mark_sick(
	struct xfs_perag	*pag,
	unsigned int		mask)
{
	ASSERT(!(mask & ~XFS_SICK_AG_PRIMARY));
	trace_xfs_ag_mark_sick(pag->pag_mount, pag->pag_agno, mask);

	spin_lock(&pag->pag_state_lock);
	pag->pag_sick |= mask;
	pag->pag_checked |= mask;
	spin_unlock(&pag->pag_state_lock);
}