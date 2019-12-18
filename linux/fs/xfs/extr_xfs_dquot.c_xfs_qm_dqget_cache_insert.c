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
struct xfs_quotainfo {int /*<<< orphan*/  qi_tree_lock; int /*<<< orphan*/  qi_dquots; } ;
struct xfs_mount {int dummy; } ;
struct xfs_dquot {int q_nrefs; } ;
struct radix_tree_root {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radix_tree_insert (struct radix_tree_root*,int /*<<< orphan*/ ,struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqget_dup (struct xfs_dquot*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_dqlock (struct xfs_dquot*) ; 

__attribute__((used)) static int
xfs_qm_dqget_cache_insert(
	struct xfs_mount	*mp,
	struct xfs_quotainfo	*qi,
	struct radix_tree_root	*tree,
	xfs_dqid_t		id,
	struct xfs_dquot	*dqp)
{
	int			error;

	mutex_lock(&qi->qi_tree_lock);
	error = radix_tree_insert(tree, id, dqp);
	if (unlikely(error)) {
		/* Duplicate found!  Caller must try again. */
		WARN_ON(error != -EEXIST);
		mutex_unlock(&qi->qi_tree_lock);
		trace_xfs_dqget_dup(dqp);
		return error;
	}

	/* Return a locked dquot to the caller, with a reference taken. */
	xfs_dqlock(dqp);
	dqp->q_nrefs = 1;

	qi->qi_dquots++;
	mutex_unlock(&qi->qi_tree_lock);

	return 0;
}