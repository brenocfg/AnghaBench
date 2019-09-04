#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct mwifiex_private {TYPE_2__* adapter; } ;
struct mwifiex_ie_types_header {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct ieee80211_regdomain {int dummy; } ;
struct host_cmd_ds_chan_region_cfg {int /*<<< orphan*/  action; } ;
struct TYPE_3__ {struct host_cmd_ds_chan_region_cfg reg_cfg; } ;
struct host_cmd_ds_command {int /*<<< orphan*/  size; TYPE_1__ params; } ;
struct TYPE_4__ {struct ieee80211_regdomain* regd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_D ; 
 scalar_t__ HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  IS_ERR (struct ieee80211_regdomain*) ; 
 scalar_t__ S_DS_GEN ; 
#define  TLV_TYPE_CHAN_ATTR_CFG 128 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ieee80211_regdomain* mwifiex_create_custom_regdomain (struct mwifiex_private*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int mwifiex_ret_chan_region_cfg(struct mwifiex_private *priv,
				       struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_chan_region_cfg *reg = &resp->params.reg_cfg;
	u16 action = le16_to_cpu(reg->action);
	u16 tlv, tlv_buf_len, tlv_buf_left;
	struct mwifiex_ie_types_header *head;
	struct ieee80211_regdomain *regd;
	u8 *tlv_buf;

	if (action != HostCmd_ACT_GEN_GET)
		return 0;

	tlv_buf = (u8 *)reg + sizeof(*reg);
	tlv_buf_left = le16_to_cpu(resp->size) - S_DS_GEN - sizeof(*reg);

	while (tlv_buf_left >= sizeof(*head)) {
		head = (struct mwifiex_ie_types_header *)tlv_buf;
		tlv = le16_to_cpu(head->type);
		tlv_buf_len = le16_to_cpu(head->len);

		if (tlv_buf_left < (sizeof(*head) + tlv_buf_len))
			break;

		switch (tlv) {
		case TLV_TYPE_CHAN_ATTR_CFG:
			mwifiex_dbg_dump(priv->adapter, CMD_D, "CHAN:",
					 (u8 *)head + sizeof(*head),
					 tlv_buf_len);
			regd = mwifiex_create_custom_regdomain(priv,
				(u8 *)head + sizeof(*head), tlv_buf_len);
			if (!IS_ERR(regd))
				priv->adapter->regd = regd;
			break;
		}

		tlv_buf += (sizeof(*head) + tlv_buf_len);
		tlv_buf_left -= (sizeof(*head) + tlv_buf_len);
	}

	return 0;
}