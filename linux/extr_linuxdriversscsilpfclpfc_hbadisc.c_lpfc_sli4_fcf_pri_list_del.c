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
typedef  size_t uint16_t ;
struct TYPE_4__ {scalar_t__ priority; } ;
struct TYPE_5__ {int /*<<< orphan*/  eligible_fcf_cnt; TYPE_1__ current_rec; struct lpfc_fcf_pri* fcf_pri; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_2__ fcf; } ;
struct TYPE_6__ {scalar_t__ priority; int flag; } ;
struct lpfc_fcf_pri {TYPE_3__ fcf_rec; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FIP ; 
 int LPFC_FCF_ON_PRI_LIST ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lpfc_sli4_fcf_pri_list_del(struct lpfc_hba *phba,
			uint16_t fcf_index)
{
	struct lpfc_fcf_pri *new_fcf_pri;

	new_fcf_pri = &phba->fcf.fcf_pri[fcf_index];
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
		"3058 deleting idx x%x pri x%x flg x%x\n",
		fcf_index, new_fcf_pri->fcf_rec.priority,
		 new_fcf_pri->fcf_rec.flag);
	spin_lock_irq(&phba->hbalock);
	if (new_fcf_pri->fcf_rec.flag & LPFC_FCF_ON_PRI_LIST) {
		if (phba->fcf.current_rec.priority ==
				new_fcf_pri->fcf_rec.priority)
			phba->fcf.eligible_fcf_cnt--;
		list_del_init(&new_fcf_pri->list);
		new_fcf_pri->fcf_rec.flag &= ~LPFC_FCF_ON_PRI_LIST;
	}
	spin_unlock_irq(&phba->hbalock);
}