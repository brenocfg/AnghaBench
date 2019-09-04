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
struct xfs_perag {int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_ici_reclaimable; int /*<<< orphan*/  pag_ici_lock; struct xfs_mount* pag_mount; } ;
struct xfs_mount {int /*<<< orphan*/  m_perag_lock; int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ICI_RECLAIM_TAG ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_perag_set_reclaim (struct xfs_mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_reclaim_work_queue (struct xfs_mount*) ; 

__attribute__((used)) static void
xfs_perag_set_reclaim_tag(
	struct xfs_perag	*pag)
{
	struct xfs_mount	*mp = pag->pag_mount;

	lockdep_assert_held(&pag->pag_ici_lock);
	if (pag->pag_ici_reclaimable++)
		return;

	/* propagate the reclaim tag up into the perag radix tree */
	spin_lock(&mp->m_perag_lock);
	radix_tree_tag_set(&mp->m_perag_tree, pag->pag_agno,
			   XFS_ICI_RECLAIM_TAG);
	spin_unlock(&mp->m_perag_lock);

	/* schedule periodic background inode reclaim */
	xfs_reclaim_work_queue(mp);

	trace_xfs_perag_set_reclaim(mp, pag->pag_agno, -1, _RET_IP_);
}