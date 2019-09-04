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
struct TYPE_2__ {int /*<<< orphan*/  scsi_xri_cnt; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; int /*<<< orphan*/  scsi_buf_list_get_lock; int /*<<< orphan*/  scsi_buf_list_put_lock; int /*<<< orphan*/  lpfc_scsi_buf_list_put; int /*<<< orphan*/  lpfc_scsi_buf_list_get; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lpfc_sli4_post_scsi_sgl_list (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_sblist ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_sli4_repost_scsi_sgl_list(struct lpfc_hba *phba)
{
	LIST_HEAD(post_sblist);
	int num_posted, rc = 0;

	/* get all SCSI buffers need to repost to a local list */
	spin_lock_irq(&phba->scsi_buf_list_get_lock);
	spin_lock(&phba->scsi_buf_list_put_lock);
	list_splice_init(&phba->lpfc_scsi_buf_list_get, &post_sblist);
	list_splice(&phba->lpfc_scsi_buf_list_put, &post_sblist);
	spin_unlock(&phba->scsi_buf_list_put_lock);
	spin_unlock_irq(&phba->scsi_buf_list_get_lock);

	/* post the list of scsi buffer sgls to port if available */
	if (!list_empty(&post_sblist)) {
		num_posted = lpfc_sli4_post_scsi_sgl_list(phba, &post_sblist,
						phba->sli4_hba.scsi_xri_cnt);
		/* failed to post any scsi buffer, return error */
		if (num_posted == 0)
			rc = -EIO;
	}
	return rc;
}