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
struct TYPE_3__ {int max_xri; } ;
struct TYPE_4__ {TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_2__ sli4_hba; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 

int
lpfc_sli4_get_els_iocb_cnt(struct lpfc_hba *phba)
{
	int max_xri = phba->sli4_hba.max_cfg_param.max_xri;

	if (phba->sli_rev == LPFC_SLI_REV4) {
		if (max_xri <= 100)
			return 10;
		else if (max_xri <= 256)
			return 25;
		else if (max_xri <= 512)
			return 50;
		else if (max_xri <= 1024)
			return 100;
		else if (max_xri <= 1536)
			return 150;
		else if (max_xri <= 2048)
			return 200;
		else
			return 250;
	} else
		return 0;
}