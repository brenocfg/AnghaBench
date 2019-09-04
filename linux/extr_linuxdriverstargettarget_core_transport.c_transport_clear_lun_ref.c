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
struct se_lun {int /*<<< orphan*/  lun_shutdown_comp; int /*<<< orphan*/  lun_ref_comp; int /*<<< orphan*/  lun_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_kill_and_confirm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_lun_confirm ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void transport_clear_lun_ref(struct se_lun *lun)
{
	/*
	 * Mark the percpu-ref as DEAD, switch to atomic_t mode, drop
	 * the initial reference and schedule confirm kill to be
	 * executed after one full RCU grace period has completed.
	 */
	percpu_ref_kill_and_confirm(&lun->lun_ref, target_lun_confirm);
	/*
	 * The first completion waits for percpu_ref_switch_to_atomic_rcu()
	 * to call target_lun_confirm after lun->lun_ref has been marked
	 * as __PERCPU_REF_DEAD on all CPUs, and switches to atomic_t
	 * mode so that percpu_ref_tryget_live() lookup of lun->lun_ref
	 * fails for all new incoming I/O.
	 */
	wait_for_completion(&lun->lun_ref_comp);
	/*
	 * The second completion waits for percpu_ref_put_many() to
	 * invoke ->release() after lun->lun_ref has switched to
	 * atomic_t mode, and lun->lun_ref.count has reached zero.
	 *
	 * At this point all target-core lun->lun_ref references have
	 * been dropped via transport_lun_remove_cmd(), and it's safe
	 * to proceed with the remaining LUN shutdown.
	 */
	wait_for_completion(&lun->lun_shutdown_comp);
}