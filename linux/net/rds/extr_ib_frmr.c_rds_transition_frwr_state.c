#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fr_state; } ;
struct TYPE_5__ {TYPE_1__ frmr; } ;
struct rds_ib_mr {TYPE_3__* ic; TYPE_2__ u; } ;
typedef  enum rds_ib_fr_state { ____Placeholder_rds_ib_fr_state } rds_ib_fr_state ;
struct TYPE_6__ {int /*<<< orphan*/  i_fastreg_inuse_count; } ;

/* Variables and functions */
 int FRMR_IS_INUSE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rds_ib_ring_empty_wait ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
rds_transition_frwr_state(struct rds_ib_mr *ibmr,
			  enum rds_ib_fr_state old_state,
			  enum rds_ib_fr_state new_state)
{
	if (cmpxchg(&ibmr->u.frmr.fr_state,
		    old_state, new_state) == old_state &&
	    old_state == FRMR_IS_INUSE) {
		/* enforce order of ibmr->u.frmr.fr_state update
		 * before decrementing i_fastreg_inuse_count
		 */
		smp_mb__before_atomic();
		atomic_dec(&ibmr->ic->i_fastreg_inuse_count);
		if (waitqueue_active(&rds_ib_ring_empty_wait))
			wake_up(&rds_ib_ring_empty_wait);
	}
}