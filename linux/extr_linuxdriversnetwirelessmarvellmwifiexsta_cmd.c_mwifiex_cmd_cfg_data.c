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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct property {int length; int /*<<< orphan*/  name; } ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {TYPE_1__* cal_data; int /*<<< orphan*/  dt_node; } ;
struct host_cmd_ds_command {void* size; void* command; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
 int HostCmd_CMD_CFG_DATA ; 
 int /*<<< orphan*/  INFO ; 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int mwifiex_parse_cal_cfg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int of_property_read_u8_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mwifiex_cmd_cfg_data(struct mwifiex_private *priv,
				struct host_cmd_ds_command *cmd, void *data_buf)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct property *prop = data_buf;
	u32 len;
	u8 *data = (u8 *)cmd + S_DS_GEN;
	int ret;

	if (prop) {
		len = prop->length;
		ret = of_property_read_u8_array(adapter->dt_node, prop->name,
						data, len);
		if (ret)
			return ret;
		mwifiex_dbg(adapter, INFO,
			    "download cfg_data from device tree: %s\n",
			    prop->name);
	} else if (adapter->cal_data->data && adapter->cal_data->size > 0) {
		len = mwifiex_parse_cal_cfg((u8 *)adapter->cal_data->data,
					    adapter->cal_data->size, data);
		mwifiex_dbg(adapter, INFO,
			    "download cfg_data from config file\n");
	} else {
		return -1;
	}

	cmd->command = cpu_to_le16(HostCmd_CMD_CFG_DATA);
	cmd->size = cpu_to_le16(S_DS_GEN + len);

	return 0;
}