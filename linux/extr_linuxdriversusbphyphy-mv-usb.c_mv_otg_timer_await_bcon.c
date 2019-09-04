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
struct timer_list {int dummy; } ;
struct TYPE_4__ {int a_wait_bcon_timeout; } ;
struct mv_otg {int /*<<< orphan*/  wq_lock; TYPE_2__* pdev; TYPE_1__ otg_ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * timer; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t A_WAIT_BCON_TIMER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct mv_otg* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_otg_run_state_machine (struct mv_otg*,int /*<<< orphan*/ ) ; 
 struct mv_otg* mvotg ; 
 TYPE_3__ otg_ctrl ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv_otg_timer_await_bcon(struct timer_list *t)
{
	struct mv_otg *mvotg = from_timer(mvotg, t,
					  otg_ctrl.timer[A_WAIT_BCON_TIMER]);

	mvotg->otg_ctrl.a_wait_bcon_timeout = 1;

	dev_info(&mvotg->pdev->dev, "B Device No Response!\n");

	if (spin_trylock(&mvotg->wq_lock)) {
		mv_otg_run_state_machine(mvotg, 0);
		spin_unlock(&mvotg->wq_lock);
	}
}