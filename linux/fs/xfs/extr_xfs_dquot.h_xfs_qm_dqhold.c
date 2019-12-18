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
struct xfs_dquot {int /*<<< orphan*/  q_nrefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_dqlock (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_dqunlock (struct xfs_dquot*) ; 

__attribute__((used)) static inline struct xfs_dquot *xfs_qm_dqhold(struct xfs_dquot *dqp)
{
	xfs_dqlock(dqp);
	dqp->q_nrefs++;
	xfs_dqunlock(dqp);
	return dqp;
}