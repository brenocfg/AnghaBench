#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  li_lv_shadow; } ;
struct TYPE_7__ {TYPE_1__ qli_item; } ;
struct TYPE_8__ {int /*<<< orphan*/  q_mount; int /*<<< orphan*/  q_qlock; TYPE_2__ q_logitem; int /*<<< orphan*/  q_lru; } ;
typedef  TYPE_3__ xfs_dquot_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_STATS_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_qm_dqzone ; 
 int /*<<< orphan*/  xs_qm_dquot ; 

void
xfs_qm_dqdestroy(
	xfs_dquot_t	*dqp)
{
	ASSERT(list_empty(&dqp->q_lru));

	kmem_free(dqp->q_logitem.qli_item.li_lv_shadow);
	mutex_destroy(&dqp->q_qlock);

	XFS_STATS_DEC(dqp->q_mount, xs_qm_dquot);
	kmem_zone_free(xfs_qm_dqzone, dqp);
}