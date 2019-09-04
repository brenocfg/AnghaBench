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
struct ufs_hba {int quirks; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POST_CHANGE ; 
 int /*<<< orphan*/  PRE_CHANGE ; 
 int /*<<< orphan*/  UFSHCD_UIC_MASK ; 
 int UFSHCI_QUIRK_BROKEN_HCE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ufshcd_dme_enable (struct ufs_hba*) ; 
 int ufshcd_dme_reset (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_enable_intr (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int ufshcd_hba_execute_hce (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_set_link_off (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vops_hce_enable_notify (struct ufs_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_hba_enable(struct ufs_hba *hba)
{
	int ret;

	if (hba->quirks & UFSHCI_QUIRK_BROKEN_HCE) {
		ufshcd_set_link_off(hba);
		ufshcd_vops_hce_enable_notify(hba, PRE_CHANGE);

		/* enable UIC related interrupts */
		ufshcd_enable_intr(hba, UFSHCD_UIC_MASK);
		ret = ufshcd_dme_reset(hba);
		if (!ret) {
			ret = ufshcd_dme_enable(hba);
			if (!ret)
				ufshcd_vops_hce_enable_notify(hba, POST_CHANGE);
			if (ret)
				dev_err(hba->dev,
					"Host controller enable failed with non-hce\n");
		}
	} else {
		ret = ufshcd_hba_execute_hce(hba);
	}

	return ret;
}