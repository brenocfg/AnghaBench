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
struct srcu_struct {int srcu_gp_running; int srcu_gp_waiting; int /*<<< orphan*/  srcu_work; scalar_t__ srcu_idx; int /*<<< orphan*/ * srcu_cb_head; int /*<<< orphan*/ ** srcu_cb_tail; int /*<<< orphan*/  srcu_wq; scalar_t__* srcu_lock_nesting; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_swait_queue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_drive_gp ; 

__attribute__((used)) static int init_srcu_struct_fields(struct srcu_struct *sp)
{
	sp->srcu_lock_nesting[0] = 0;
	sp->srcu_lock_nesting[1] = 0;
	init_swait_queue_head(&sp->srcu_wq);
	sp->srcu_cb_head = NULL;
	sp->srcu_cb_tail = &sp->srcu_cb_head;
	sp->srcu_gp_running = false;
	sp->srcu_gp_waiting = false;
	sp->srcu_idx = 0;
	INIT_WORK(&sp->srcu_work, srcu_drive_gp);
	return 0;
}