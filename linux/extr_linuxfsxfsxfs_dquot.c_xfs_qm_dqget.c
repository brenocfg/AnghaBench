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
typedef  int /*<<< orphan*/  uint ;
struct xfs_quotainfo {int dummy; } ;
struct xfs_mount {struct xfs_quotainfo* m_quotainfo; } ;
struct xfs_dquot {int dummy; } ;
struct radix_tree_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dqget_miss (struct xfs_dquot*) ; 
 struct radix_tree_root* xfs_dquot_tree (struct xfs_quotainfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_qm_dqdestroy (struct xfs_dquot*) ; 
 int xfs_qm_dqget_cache_insert (struct xfs_mount*,struct xfs_quotainfo*,struct radix_tree_root*,int /*<<< orphan*/ ,struct xfs_dquot*) ; 
 struct xfs_dquot* xfs_qm_dqget_cache_lookup (struct xfs_mount*,struct xfs_quotainfo*,struct radix_tree_root*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqget_checks (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqread (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_dquot**) ; 
 int /*<<< orphan*/  xs_qm_dquot_dups ; 

int
xfs_qm_dqget(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	bool			can_alloc,
	struct xfs_dquot	**O_dqpp)
{
	struct xfs_quotainfo	*qi = mp->m_quotainfo;
	struct radix_tree_root	*tree = xfs_dquot_tree(qi, type);
	struct xfs_dquot	*dqp;
	int			error;

	error = xfs_qm_dqget_checks(mp, type);
	if (error)
		return error;

restart:
	dqp = xfs_qm_dqget_cache_lookup(mp, qi, tree, id);
	if (dqp) {
		*O_dqpp = dqp;
		return 0;
	}

	error = xfs_qm_dqread(mp, id, type, can_alloc, &dqp);
	if (error)
		return error;

	error = xfs_qm_dqget_cache_insert(mp, qi, tree, id, dqp);
	if (error) {
		/*
		 * Duplicate found. Just throw away the new dquot and start
		 * over.
		 */
		xfs_qm_dqdestroy(dqp);
		XFS_STATS_INC(mp, xs_qm_dquot_dups);
		goto restart;
	}

	trace_xfs_dqget_miss(dqp);
	*O_dqpp = dqp;
	return 0;
}