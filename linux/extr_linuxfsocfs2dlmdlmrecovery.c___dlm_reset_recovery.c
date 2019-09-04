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
struct TYPE_2__ {int /*<<< orphan*/  dead_node; } ;
struct dlm_ctxt {int /*<<< orphan*/  recovery_map; TYPE_1__ reco; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  O2NM_INVALID_NODE_NUM ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_set_reco_dead_node (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_set_reco_master (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __dlm_reset_recovery(struct dlm_ctxt *dlm)
{
	assert_spin_locked(&dlm->spinlock);
	clear_bit(dlm->reco.dead_node, dlm->recovery_map);
	dlm_set_reco_dead_node(dlm, O2NM_INVALID_NODE_NUM);
	dlm_set_reco_master(dlm, O2NM_INVALID_NODE_NUM);
}