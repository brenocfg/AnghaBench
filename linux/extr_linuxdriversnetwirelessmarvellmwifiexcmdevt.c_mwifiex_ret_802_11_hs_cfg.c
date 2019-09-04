#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {scalar_t__ iface_type; scalar_t__ hs_activated; int /*<<< orphan*/  work_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  gap; int /*<<< orphan*/  gpio; int /*<<< orphan*/  conditions; } ;
struct TYPE_6__ {TYPE_2__ hs_config; } ;
struct host_cmd_ds_802_11_hs_cfg_enh {scalar_t__ action; TYPE_3__ params; } ;
struct TYPE_4__ {struct host_cmd_ds_802_11_hs_cfg_enh opt_hs_cfg; } ;
struct host_cmd_ds_command {int /*<<< orphan*/  result; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  HS_ACTIVATE ; 
 scalar_t__ HS_CFG_CANCEL ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_CONFIGURED ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_hs_activated_event (struct mwifiex_private*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mwifiex_ret_802_11_hs_cfg(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_ds_802_11_hs_cfg_enh *phs_cfg =
		&resp->params.opt_hs_cfg;
	uint32_t conditions = le32_to_cpu(phs_cfg->params.hs_config.conditions);

	if (phs_cfg->action == cpu_to_le16(HS_ACTIVATE) &&
	    adapter->iface_type != MWIFIEX_USB) {
		mwifiex_hs_activated_event(priv, true);
		return 0;
	} else {
		mwifiex_dbg(adapter, CMD,
			    "cmd: CMD_RESP: HS_CFG cmd reply\t"
			    " result=%#x, conditions=0x%x gpio=0x%x gap=0x%x\n",
			    resp->result, conditions,
			    phs_cfg->params.hs_config.gpio,
			    phs_cfg->params.hs_config.gap);
	}
	if (conditions != HS_CFG_CANCEL) {
		set_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
		if (adapter->iface_type == MWIFIEX_USB)
			mwifiex_hs_activated_event(priv, true);
	} else {
		clear_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
		if (adapter->hs_activated)
			mwifiex_hs_activated_event(priv, false);
	}

	return 0;
}