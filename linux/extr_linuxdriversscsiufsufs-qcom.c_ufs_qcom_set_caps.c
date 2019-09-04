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
struct TYPE_2__ {int major; } ;
struct ufs_qcom_host {int caps; TYPE_1__ hw_ver; } ;
struct ufs_hba {int caps; } ;

/* Variables and functions */
 int UFSHCD_CAP_AUTO_BKOPS_SUSPEND ; 
 int UFSHCD_CAP_CLK_GATING ; 
 int UFSHCD_CAP_CLK_SCALING ; 
 int UFSHCD_CAP_HIBERN8_WITH_CLK_GATING ; 
 int UFS_QCOM_CAP_QUNIPRO ; 
 int UFS_QCOM_CAP_RETAIN_SEC_CFG_AFTER_PWR_COLLAPSE ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static void ufs_qcom_set_caps(struct ufs_hba *hba)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);

	hba->caps |= UFSHCD_CAP_CLK_GATING | UFSHCD_CAP_HIBERN8_WITH_CLK_GATING;
	hba->caps |= UFSHCD_CAP_CLK_SCALING;
	hba->caps |= UFSHCD_CAP_AUTO_BKOPS_SUSPEND;

	if (host->hw_ver.major >= 0x2) {
		host->caps = UFS_QCOM_CAP_QUNIPRO |
			     UFS_QCOM_CAP_RETAIN_SEC_CFG_AFTER_PWR_COLLAPSE;
	}
}