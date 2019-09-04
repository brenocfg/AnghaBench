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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ drbl_regs_memmap_p; scalar_t__ BMBXregaddr; scalar_t__ MQDBregaddr; scalar_t__ CQDBregaddr; scalar_t__ EQDBregaddr; scalar_t__ WQDBregaddr; scalar_t__ RQDBregaddr; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ LPFC_BMBX ; 
 scalar_t__ LPFC_EQCQ_DOORBELL ; 
 scalar_t__ LPFC_MQ_DOORBELL ; 
 scalar_t__ LPFC_ULP0_RQ_DOORBELL ; 
 scalar_t__ LPFC_ULP0_WQ_DOORBELL ; 
 int LPFC_VFR_PAGE_SIZE ; 
 int LPFC_VIR_FUNC_MAX ; 

__attribute__((used)) static int
lpfc_sli4_bar2_register_memmap(struct lpfc_hba *phba, uint32_t vf)
{
	if (vf > LPFC_VIR_FUNC_MAX)
		return -ENODEV;

	phba->sli4_hba.RQDBregaddr = (phba->sli4_hba.drbl_regs_memmap_p +
				vf * LPFC_VFR_PAGE_SIZE +
					LPFC_ULP0_RQ_DOORBELL);
	phba->sli4_hba.WQDBregaddr = (phba->sli4_hba.drbl_regs_memmap_p +
				vf * LPFC_VFR_PAGE_SIZE +
					LPFC_ULP0_WQ_DOORBELL);
	phba->sli4_hba.CQDBregaddr = (phba->sli4_hba.drbl_regs_memmap_p +
				vf * LPFC_VFR_PAGE_SIZE +
					LPFC_EQCQ_DOORBELL);
	phba->sli4_hba.EQDBregaddr = phba->sli4_hba.CQDBregaddr;
	phba->sli4_hba.MQDBregaddr = (phba->sli4_hba.drbl_regs_memmap_p +
				vf * LPFC_VFR_PAGE_SIZE + LPFC_MQ_DOORBELL);
	phba->sli4_hba.BMBXregaddr = (phba->sli4_hba.drbl_regs_memmap_p +
				vf * LPFC_VFR_PAGE_SIZE + LPFC_BMBX);
	return 0;
}