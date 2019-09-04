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
struct TYPE_6__ {int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/  iotag; int /*<<< orphan*/  sli4_xritag; } ;
struct lpfc_nvme_buf {int flags; int /*<<< orphan*/  list; TYPE_3__ cur_iocbq; int /*<<< orphan*/ * nvmeCmd; TYPE_1__* ndlp; scalar_t__ nonsg_phys; } ;
struct TYPE_5__ {int /*<<< orphan*/  abts_nvme_buf_list_lock; int /*<<< orphan*/  lpfc_abts_nvme_buf_list; } ;
struct lpfc_hba {int /*<<< orphan*/  nvme_buf_list_put_lock; int /*<<< orphan*/  put_nvme_bufs; int /*<<< orphan*/  lpfc_nvme_buf_list_put; TYPE_2__ sli4_hba; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int LPFC_BUMP_QDEPTH ; 
 int /*<<< orphan*/  LPFC_IO_NVME ; 
 int LPFC_SBUF_XBUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_release_nvme_buf(struct lpfc_hba *phba, struct lpfc_nvme_buf *lpfc_ncmd)
{
	unsigned long iflag = 0;

	if ((lpfc_ncmd->flags & LPFC_BUMP_QDEPTH) && lpfc_ncmd->ndlp)
		atomic_dec(&lpfc_ncmd->ndlp->cmd_pending);

	lpfc_ncmd->nonsg_phys = 0;
	lpfc_ncmd->ndlp = NULL;
	lpfc_ncmd->flags &= ~LPFC_BUMP_QDEPTH;

	if (lpfc_ncmd->flags & LPFC_SBUF_XBUSY) {
		lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
				"6310 XB release deferred for "
				"ox_id x%x on reqtag x%x\n",
				lpfc_ncmd->cur_iocbq.sli4_xritag,
				lpfc_ncmd->cur_iocbq.iotag);

		spin_lock_irqsave(&phba->sli4_hba.abts_nvme_buf_list_lock,
					iflag);
		list_add_tail(&lpfc_ncmd->list,
			&phba->sli4_hba.lpfc_abts_nvme_buf_list);
		spin_unlock_irqrestore(&phba->sli4_hba.abts_nvme_buf_list_lock,
					iflag);
	} else {
		lpfc_ncmd->nvmeCmd = NULL;
		lpfc_ncmd->cur_iocbq.iocb_flag = LPFC_IO_NVME;
		spin_lock_irqsave(&phba->nvme_buf_list_put_lock, iflag);
		list_add_tail(&lpfc_ncmd->list, &phba->lpfc_nvme_buf_list_put);
		phba->put_nvme_bufs++;
		spin_unlock_irqrestore(&phba->nvme_buf_list_put_lock, iflag);
	}
}