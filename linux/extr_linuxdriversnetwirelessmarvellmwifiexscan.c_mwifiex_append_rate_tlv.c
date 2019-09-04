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
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_scan_cmd_config {int tlv_buf_len; scalar_t__ tlv_buf; } ;
struct mwifiex_private {int /*<<< orphan*/  adapter; scalar_t__ scan_request; } ;
struct TYPE_2__ {void* len; void* type; } ;
struct mwifiex_ie_types_rates_param_set {int /*<<< orphan*/  rates; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  rates ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int MWIFIEX_SUPPORTED_RATES ; 
 int /*<<< orphan*/  WLAN_EID_SUPP_RATES ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int mwifiex_get_rates_from_cfg80211 (struct mwifiex_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mwifiex_get_supported_rates (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwifiex_append_rate_tlv(struct mwifiex_private *priv,
			struct mwifiex_scan_cmd_config *scan_cfg_out,
			u8 radio)
{
	struct mwifiex_ie_types_rates_param_set *rates_tlv;
	u8 rates[MWIFIEX_SUPPORTED_RATES], *tlv_pos;
	u32 rates_size;

	memset(rates, 0, sizeof(rates));

	tlv_pos = (u8 *)scan_cfg_out->tlv_buf + scan_cfg_out->tlv_buf_len;

	if (priv->scan_request)
		rates_size = mwifiex_get_rates_from_cfg80211(priv, rates,
							     radio);
	else
		rates_size = mwifiex_get_supported_rates(priv, rates);

	mwifiex_dbg(priv->adapter, CMD,
		    "info: SCAN_CMD: Rates size = %d\n",
		rates_size);
	rates_tlv = (struct mwifiex_ie_types_rates_param_set *)tlv_pos;
	rates_tlv->header.type = cpu_to_le16(WLAN_EID_SUPP_RATES);
	rates_tlv->header.len = cpu_to_le16((u16) rates_size);
	memcpy(rates_tlv->rates, rates, rates_size);
	scan_cfg_out->tlv_buf_len += sizeof(rates_tlv->header) + rates_size;

	return rates_size;
}