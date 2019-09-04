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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct uic_command {int /*<<< orphan*/  argument3; int /*<<< orphan*/  argument1; int /*<<< orphan*/  command; int /*<<< orphan*/  member_0; } ;
struct ufs_pa_layer_attr {scalar_t__ pwr_tx; scalar_t__ pwr_rx; } ;
struct ufs_hba {int quirks; int /*<<< orphan*/  dev; struct ufs_pa_layer_attr pwr_info; } ;

/* Variables and functions */
 void* FASTAUTO_MODE ; 
 scalar_t__ FAST_MODE ; 
 void* SLOWAUTO_MODE ; 
 scalar_t__ SLOW_MODE ; 
 int UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE ; 
 int UFS_UIC_COMMAND_RETRIES ; 
 int /*<<< orphan*/  UIC_CMD_DME_GET ; 
 int /*<<< orphan*/  UIC_CMD_DME_PEER_GET ; 
 int /*<<< orphan*/  UIC_GET_ATTR_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int) ; 
 int ufshcd_change_power_mode (struct ufs_hba*,struct ufs_pa_layer_attr*) ; 
 int ufshcd_send_uic_cmd (struct ufs_hba*,struct uic_command*) ; 

int ufshcd_dme_get_attr(struct ufs_hba *hba, u32 attr_sel,
			u32 *mib_val, u8 peer)
{
	struct uic_command uic_cmd = {0};
	static const char *const action[] = {
		"dme-get",
		"dme-peer-get"
	};
	const char *get = action[!!peer];
	int ret;
	int retries = UFS_UIC_COMMAND_RETRIES;
	struct ufs_pa_layer_attr orig_pwr_info;
	struct ufs_pa_layer_attr temp_pwr_info;
	bool pwr_mode_change = false;

	if (peer && (hba->quirks & UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE)) {
		orig_pwr_info = hba->pwr_info;
		temp_pwr_info = orig_pwr_info;

		if (orig_pwr_info.pwr_tx == FAST_MODE ||
		    orig_pwr_info.pwr_rx == FAST_MODE) {
			temp_pwr_info.pwr_tx = FASTAUTO_MODE;
			temp_pwr_info.pwr_rx = FASTAUTO_MODE;
			pwr_mode_change = true;
		} else if (orig_pwr_info.pwr_tx == SLOW_MODE ||
		    orig_pwr_info.pwr_rx == SLOW_MODE) {
			temp_pwr_info.pwr_tx = SLOWAUTO_MODE;
			temp_pwr_info.pwr_rx = SLOWAUTO_MODE;
			pwr_mode_change = true;
		}
		if (pwr_mode_change) {
			ret = ufshcd_change_power_mode(hba, &temp_pwr_info);
			if (ret)
				goto out;
		}
	}

	uic_cmd.command = peer ?
		UIC_CMD_DME_PEER_GET : UIC_CMD_DME_GET;
	uic_cmd.argument1 = attr_sel;

	do {
		/* for peer attributes we retry upon failure */
		ret = ufshcd_send_uic_cmd(hba, &uic_cmd);
		if (ret)
			dev_dbg(hba->dev, "%s: attr-id 0x%x error code %d\n",
				get, UIC_GET_ATTR_ID(attr_sel), ret);
	} while (ret && peer && --retries);

	if (ret)
		dev_err(hba->dev, "%s: attr-id 0x%x failed %d retries\n",
			get, UIC_GET_ATTR_ID(attr_sel),
			UFS_UIC_COMMAND_RETRIES - retries);

	if (mib_val && !ret)
		*mib_val = uic_cmd.argument3;

	if (peer && (hba->quirks & UFSHCD_QUIRK_DME_PEER_ACCESS_AUTO_MODE)
	    && pwr_mode_change)
		ufshcd_change_power_mode(hba, &orig_pwr_info);
out:
	return ret;
}