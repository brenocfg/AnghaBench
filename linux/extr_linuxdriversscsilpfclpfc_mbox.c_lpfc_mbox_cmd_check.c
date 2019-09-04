#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hba {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_6__ {TYPE_1__ mb; } ;
struct TYPE_7__ {scalar_t__ mbox_cmpl; TYPE_2__ u; int /*<<< orphan*/  vport; } ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_MBOX ; 
 int LOG_VPORT ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_sli_def_mbox_cmpl ; 
 scalar_t__ lpfc_sli_wake_mbox_wait ; 

int
lpfc_mbox_cmd_check(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq)
{
	/* Mailbox command that have a completion handler must also have a
	 * vport specified.
	 */
	if (mboxq->mbox_cmpl && mboxq->mbox_cmpl != lpfc_sli_def_mbox_cmpl &&
	    mboxq->mbox_cmpl != lpfc_sli_wake_mbox_wait) {
		if (!mboxq->vport) {
			lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_VPORT,
					"1814 Mbox x%x failed, no vport\n",
					mboxq->u.mb.mbxCommand);
			dump_stack();
			return -ENODEV;
		}
	}
	return 0;
}