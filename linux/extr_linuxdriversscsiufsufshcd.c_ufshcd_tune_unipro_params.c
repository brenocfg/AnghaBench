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
struct ufs_hba {int dev_quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA_TACTIVATE ; 
 int UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE ; 
 int UFS_DEVICE_QUIRK_PA_TACTIVATE ; 
 int /*<<< orphan*/  UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_dme_set (struct ufs_hba*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ufshcd_is_unipro_pa_params_tuning_req (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_quirk_tune_host_pa_tactivate (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_tune_pa_hibern8time (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_tune_pa_tactivate (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vops_apply_dev_quirks (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_tune_unipro_params(struct ufs_hba *hba)
{
	if (ufshcd_is_unipro_pa_params_tuning_req(hba)) {
		ufshcd_tune_pa_tactivate(hba);
		ufshcd_tune_pa_hibern8time(hba);
	}

	if (hba->dev_quirks & UFS_DEVICE_QUIRK_PA_TACTIVATE)
		/* set 1ms timeout for PA_TACTIVATE */
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE), 10);

	if (hba->dev_quirks & UFS_DEVICE_QUIRK_HOST_PA_TACTIVATE)
		ufshcd_quirk_tune_host_pa_tactivate(hba);

	ufshcd_vops_apply_dev_quirks(hba);
}