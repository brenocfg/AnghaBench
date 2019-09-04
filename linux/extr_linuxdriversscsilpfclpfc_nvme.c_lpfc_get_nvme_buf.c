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
struct lpfc_nvme_buf {int /*<<< orphan*/  flags; } ;
struct lpfc_nodelist {int /*<<< orphan*/  cmd_pending; } ;
struct lpfc_hba {scalar_t__ get_nvme_bufs; scalar_t__ put_nvme_bufs; int /*<<< orphan*/  nvme_buf_list_get_lock; int /*<<< orphan*/  nvme_buf_list_put_lock; int /*<<< orphan*/  lpfc_nvme_buf_list_put; int /*<<< orphan*/  lpfc_nvme_buf_list_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPFC_BUMP_QDEPTH ; 
 scalar_t__ LPFC_NVME_EXPEDITE_XRICNT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_ndlp_check_qdepth (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 struct lpfc_nvme_buf* lpfc_nvme_buf (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct lpfc_nvme_buf *
lpfc_get_nvme_buf(struct lpfc_hba *phba, struct lpfc_nodelist *ndlp,
		  int expedite)
{
	struct lpfc_nvme_buf *lpfc_ncmd = NULL;
	unsigned long iflag = 0;

	spin_lock_irqsave(&phba->nvme_buf_list_get_lock, iflag);
	if (phba->get_nvme_bufs > LPFC_NVME_EXPEDITE_XRICNT || expedite)
		lpfc_ncmd = lpfc_nvme_buf(phba);
	if (!lpfc_ncmd) {
		spin_lock(&phba->nvme_buf_list_put_lock);
		list_splice(&phba->lpfc_nvme_buf_list_put,
			    &phba->lpfc_nvme_buf_list_get);
		phba->get_nvme_bufs += phba->put_nvme_bufs;
		INIT_LIST_HEAD(&phba->lpfc_nvme_buf_list_put);
		phba->put_nvme_bufs = 0;
		spin_unlock(&phba->nvme_buf_list_put_lock);
		if (phba->get_nvme_bufs > LPFC_NVME_EXPEDITE_XRICNT || expedite)
			lpfc_ncmd = lpfc_nvme_buf(phba);
	}
	spin_unlock_irqrestore(&phba->nvme_buf_list_get_lock, iflag);

	if (lpfc_ndlp_check_qdepth(phba, ndlp) && lpfc_ncmd) {
		atomic_inc(&ndlp->cmd_pending);
		lpfc_ncmd->flags |= LPFC_BUMP_QDEPTH;
	}
	return  lpfc_ncmd;
}