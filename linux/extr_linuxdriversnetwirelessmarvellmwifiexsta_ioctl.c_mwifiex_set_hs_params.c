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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_ds_hs_cfg {void* gap; void* gpio; void* conditions; int /*<<< orphan*/  is_invoke_hostcmd; } ;
struct TYPE_2__ {void* conditions; void* gap; void* gpio; } ;
struct mwifiex_adapter {TYPE_1__ hs_cfg; int /*<<< orphan*/  work_flags; int /*<<< orphan*/  pps_uapsd_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* HS_CFG_CANCEL ; 
#define  HostCmd_ACT_GEN_GET 129 
#define  HostCmd_ACT_GEN_SET 128 
 int /*<<< orphan*/  HostCmd_CMD_802_11_HS_CFG_ENH ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_CONFIGURED ; 
 int MWIFIEX_SYNC_CMD ; 
 void* cpu_to_le32 (void*) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mwifiex_set_hs_params(struct mwifiex_private *priv, u16 action,
			  int cmd_type, struct mwifiex_ds_hs_cfg *hs_cfg)

{
	struct mwifiex_adapter *adapter = priv->adapter;
	int status = 0;
	u32 prev_cond = 0;

	if (!hs_cfg)
		return -ENOMEM;

	switch (action) {
	case HostCmd_ACT_GEN_SET:
		if (adapter->pps_uapsd_mode) {
			mwifiex_dbg(adapter, INFO,
				    "info: Host Sleep IOCTL\t"
				    "is blocked in UAPSD/PPS mode\n");
			status = -1;
			break;
		}
		if (hs_cfg->is_invoke_hostcmd) {
			if (hs_cfg->conditions == HS_CFG_CANCEL) {
				if (!test_bit(MWIFIEX_IS_HS_CONFIGURED,
					      &adapter->work_flags))
					/* Already cancelled */
					break;
				/* Save previous condition */
				prev_cond = le32_to_cpu(adapter->hs_cfg
							.conditions);
				adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
			} else if (hs_cfg->conditions) {
				adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
				adapter->hs_cfg.gpio = (u8)hs_cfg->gpio;
				if (hs_cfg->gap)
					adapter->hs_cfg.gap = (u8)hs_cfg->gap;
			} else if (adapter->hs_cfg.conditions ==
				   cpu_to_le32(HS_CFG_CANCEL)) {
				/* Return failure if no parameters for HS
				   enable */
				status = -1;
				break;
			}

			status = mwifiex_send_cmd(priv,
						  HostCmd_CMD_802_11_HS_CFG_ENH,
						  HostCmd_ACT_GEN_SET, 0,
						  &adapter->hs_cfg,
						  cmd_type == MWIFIEX_SYNC_CMD);

			if (hs_cfg->conditions == HS_CFG_CANCEL)
				/* Restore previous condition */
				adapter->hs_cfg.conditions =
						cpu_to_le32(prev_cond);
		} else {
			adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
			adapter->hs_cfg.gpio = (u8)hs_cfg->gpio;
			adapter->hs_cfg.gap = (u8)hs_cfg->gap;
		}
		break;
	case HostCmd_ACT_GEN_GET:
		hs_cfg->conditions = le32_to_cpu(adapter->hs_cfg.conditions);
		hs_cfg->gpio = adapter->hs_cfg.gpio;
		hs_cfg->gap = adapter->hs_cfg.gap;
		break;
	default:
		status = -1;
		break;
	}

	return status;
}