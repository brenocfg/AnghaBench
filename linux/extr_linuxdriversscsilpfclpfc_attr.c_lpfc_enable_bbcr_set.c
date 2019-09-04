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
typedef  int /*<<< orphan*/  uint ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  cfg_enable_bbcr; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_DRIVER_NAME ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ lpfc_rangecheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
lpfc_enable_bbcr_set(struct lpfc_hba *phba, uint val)
{
	if (lpfc_rangecheck(val, 0, 1) && phba->sli_rev == LPFC_SLI_REV4) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"3068 %s_enable_bbcr changed from %d to %d\n",
				LPFC_DRIVER_NAME, phba->cfg_enable_bbcr, val);
		phba->cfg_enable_bbcr = val;
		return 0;
	}
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"0451 %s_enable_bbcr cannot set to %d, range is 0, 1\n",
			LPFC_DRIVER_NAME, val);
	return -EINVAL;
}