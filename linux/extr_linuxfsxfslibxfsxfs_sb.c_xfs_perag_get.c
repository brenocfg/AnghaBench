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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_perag {int /*<<< orphan*/  pag_ref; } ;
struct xfs_mount {int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct xfs_perag* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct xfs_perag *
xfs_perag_get(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno)
{
	struct xfs_perag	*pag;
	int			ref = 0;

	rcu_read_lock();
	pag = radix_tree_lookup(&mp->m_perag_tree, agno);
	if (pag) {
		ASSERT(atomic_read(&pag->pag_ref) >= 0);
		ref = atomic_inc_return(&pag->pag_ref);
	}
	rcu_read_unlock();
	trace_xfs_perag_get(mp, agno, ref, _RET_IP_);
	return pag;
}