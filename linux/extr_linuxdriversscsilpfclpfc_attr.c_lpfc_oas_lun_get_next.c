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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_name {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oas_next_lun; scalar_t__ oas_next_tgt_wwpn; scalar_t__ oas_next_vpt_wwpn; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_OAS_ENABLED_LUN ; 
 scalar_t__ lpfc_find_next_oas_lun (struct lpfc_hba*,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ *,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static uint64_t
lpfc_oas_lun_get_next(struct lpfc_hba *phba, uint8_t vpt_wwpn[],
		      uint8_t tgt_wwpn[], uint32_t *lun_status,
		      uint32_t *lun_pri)
{
	uint64_t found_lun;

	if (unlikely(!phba) || !vpt_wwpn || !tgt_wwpn)
		return NOT_OAS_ENABLED_LUN;
	if (lpfc_find_next_oas_lun(phba, (struct lpfc_name *)
				   phba->sli4_hba.oas_next_vpt_wwpn,
				   (struct lpfc_name *)
				   phba->sli4_hba.oas_next_tgt_wwpn,
				   &phba->sli4_hba.oas_next_lun,
				   (struct lpfc_name *)vpt_wwpn,
				   (struct lpfc_name *)tgt_wwpn,
				   &found_lun, lun_status, lun_pri))
		return found_lun;
	else
		return NOT_OAS_ENABLED_LUN;
}