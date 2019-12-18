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
struct srcu_struct {int srcu_gp_running; int srcu_gp_waiting; int srcu_cb_head; int* srcu_cb_tail; int /*<<< orphan*/  srcu_work; scalar_t__* srcu_lock_nesting; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 

void cleanup_srcu_struct(struct srcu_struct *ssp)
{
	WARN_ON(ssp->srcu_lock_nesting[0] || ssp->srcu_lock_nesting[1]);
	flush_work(&ssp->srcu_work);
	WARN_ON(ssp->srcu_gp_running);
	WARN_ON(ssp->srcu_gp_waiting);
	WARN_ON(ssp->srcu_cb_head);
	WARN_ON(&ssp->srcu_cb_head != ssp->srcu_cb_tail);
}