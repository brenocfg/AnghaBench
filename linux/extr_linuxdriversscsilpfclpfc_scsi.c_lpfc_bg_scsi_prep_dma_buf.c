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
struct lpfc_scsi_buf {int dummy; } ;
struct lpfc_hba {int (* lpfc_bg_scsi_prep_dma_buf ) (struct lpfc_hba*,struct lpfc_scsi_buf*) ;} ;

/* Variables and functions */
 int stub1 (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 

__attribute__((used)) static inline int
lpfc_bg_scsi_prep_dma_buf(struct lpfc_hba *phba, struct lpfc_scsi_buf *lpfc_cmd)
{
	return phba->lpfc_bg_scsi_prep_dma_buf(phba, lpfc_cmd);
}