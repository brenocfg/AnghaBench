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
struct ufs_qcom_host {int dummy; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ufs_qcom_cap_qunipro (struct ufs_qcom_host*) ; 
 int ufs_qcom_set_dme_vs_core_clk_ctrl_clear_div (struct ufs_hba*,int) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static int ufs_qcom_clk_scale_up_post_change(struct ufs_hba *hba)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);

	if (!ufs_qcom_cap_qunipro(host))
		return 0;

	/* set unipro core clock cycles to 150 and clear clock divider */
	return ufs_qcom_set_dme_vs_core_clk_ctrl_clear_div(hba, 150);
}