#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int fcf_flag; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;
struct TYPE_4__ {int /*<<< orphan*/  redisc_wait; } ;

/* Variables and functions */
 int FCF_REDISC_EVT ; 
 int FCF_REDISC_PEND ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FIP ; 
 TYPE_2__ fcf ; 
 struct lpfc_hba* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 struct lpfc_hba* phba ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_sli4_fcf_redisc_wait_tmo(struct timer_list *t)
{
	struct lpfc_hba *phba = from_timer(phba, t, fcf.redisc_wait);

	/* Don't send FCF rediscovery event if timer cancelled */
	spin_lock_irq(&phba->hbalock);
	if (!(phba->fcf.fcf_flag & FCF_REDISC_PEND)) {
		spin_unlock_irq(&phba->hbalock);
		return;
	}
	/* Clear FCF rediscovery timer pending flag */
	phba->fcf.fcf_flag &= ~FCF_REDISC_PEND;
	/* FCF rediscovery event to worker thread */
	phba->fcf.fcf_flag |= FCF_REDISC_EVT;
	spin_unlock_irq(&phba->hbalock);
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2776 FCF rediscover quiescent timer expired\n");
	/* wake up worker thread */
	lpfc_worker_wake_up(phba);
}