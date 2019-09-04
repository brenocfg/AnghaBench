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
struct uic_command {int /*<<< orphan*/  command; int /*<<< orphan*/  member_0; } ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIC_CMD_DME_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ufshcd_send_uic_cmd (struct ufs_hba*,struct uic_command*) ; 

__attribute__((used)) static int ufshcd_dme_enable(struct ufs_hba *hba)
{
	struct uic_command uic_cmd = {0};
	int ret;

	uic_cmd.command = UIC_CMD_DME_ENABLE;

	ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
	if (ret)
		dev_err(hba->dev,
			"dme-reset: error code %d\n", ret);

	return ret;
}