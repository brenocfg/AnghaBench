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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct beiscsi_hba {TYPE_1__ hw_check; int /*<<< orphan*/  state; int /*<<< orphan*/  sess_work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_UER_SUPP ; 
 int /*<<< orphan*/  BEISCSI_UE_DETECT_INTERVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ beiscsi_detect_ue (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_hw_tpe_check ; 
 struct beiscsi_hba* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_check ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct beiscsi_hba* phba ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_hw_health_check(struct timer_list *t)
{
	struct beiscsi_hba *phba = from_timer(phba, t, hw_check);

	beiscsi_detect_ue(phba);
	if (beiscsi_detect_ue(phba)) {
		__beiscsi_log(phba, KERN_ERR,
			      "BM_%d : port in error: %lx\n", phba->state);
		/* sessions are no longer valid, so first fail the sessions */
		queue_work(phba->wq, &phba->sess_work);

		/* detect UER supported */
		if (!test_bit(BEISCSI_HBA_UER_SUPP, &phba->state))
			return;
		/* modify this timer to check TPE */
		phba->hw_check.function = beiscsi_hw_tpe_check;
	}

	mod_timer(&phba->hw_check,
		  jiffies + msecs_to_jiffies(BEISCSI_UE_DETECT_INTERVAL));
}