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
typedef  int /*<<< orphan*/  xfs_dqid_t ;
struct xfs_quotainfo {int /*<<< orphan*/  qi_tree_lock; } ;
struct xfs_mount {int dummy; } ;
struct xfs_dquot {int dq_flags; int /*<<< orphan*/  q_nrefs; } ;
struct radix_tree_root {int dummy; } ;

/* Variables and functions */
 int XFS_DQ_FREEING ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xfs_dquot* radix_tree_lookup (struct radix_tree_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dqget_freeing (struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqget_hit (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dqlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dqunlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xs_qm_dqcachehits ; 
 int /*<<< orphan*/  xs_qm_dqcachemisses ; 

__attribute__((used)) static struct xfs_dquot *
xfs_qm_dqget_cache_lookup(
	struct xfs_mount	*mp,
	struct xfs_quotainfo	*qi,
	struct radix_tree_root	*tree,
	xfs_dqid_t		id)
{
	struct xfs_dquot	*dqp;

restart:
	mutex_lock(&qi->qi_tree_lock);
	dqp = radix_tree_lookup(tree, id);
	if (!dqp) {
		mutex_unlock(&qi->qi_tree_lock);
		XFS_STATS_INC(mp, xs_qm_dqcachemisses);
		return NULL;
	}

	xfs_dqlock(dqp);
	if (dqp->dq_flags & XFS_DQ_FREEING) {
		xfs_dqunlock(dqp);
		mutex_unlock(&qi->qi_tree_lock);
		trace_xfs_dqget_freeing(dqp);
		delay(1);
		goto restart;
	}

	dqp->q_nrefs++;
	mutex_unlock(&qi->qi_tree_lock);

	trace_xfs_dqget_hit(dqp);
	XFS_STATS_INC(mp, xs_qm_dqcachehits);
	return dqp;
}