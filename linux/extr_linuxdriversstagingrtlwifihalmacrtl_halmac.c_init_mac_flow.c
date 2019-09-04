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
typedef  scalar_t__ u8 ;
struct rtl_priv {TYPE_1__* cfg; } ;
struct halmac_api {int (* halmac_init_mac_cfg ) (struct halmac_adapter*,int /*<<< orphan*/ ) ;int (* halmac_cfg_operation_mode ) (struct halmac_adapter*,int /*<<< orphan*/ ) ;} ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
struct TYPE_2__ {scalar_t__* maps; } ;

/* Variables and functions */
 struct halmac_api* HALMAC_GET_API (struct halmac_adapter*) ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_TRX_MODE_NORMAL ; 
 int /*<<< orphan*/  HALMAC_TRX_MODE_WMM ; 
 int /*<<< orphan*/  HALMAC_WIRELESS_MODE_AC ; 
 int /*<<< orphan*/  HALMAC_WIRELESS_MODE_B ; 
 int /*<<< orphan*/  HALMAC_WIRELESS_MODE_G ; 
 int /*<<< orphan*/  HALMAC_WIRELESS_MODE_N ; 
 size_t RTL_RC_HT_RATEMCS7 ; 
 size_t RTL_RC_OFDM_RATE6M ; 
 size_t RTL_RC_VHT_RATE_1SS_MCS7 ; 
 int rtl_halmac_rx_agg_switch (struct rtl_priv*,int) ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 
 int stub1 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int stub2 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int stub3 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int stub4 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int stub5 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int stub6 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum halmac_ret_status init_mac_flow(struct rtl_priv *rtlpriv)
{
	struct halmac_adapter *halmac;
	struct halmac_api *api;
	enum halmac_ret_status status;
	u8 wifi_test = 0;
	int err;

	halmac = rtlpriv_to_halmac(rtlpriv);
	api = HALMAC_GET_API(halmac);

	if (wifi_test)
		status = api->halmac_init_mac_cfg(halmac, HALMAC_TRX_MODE_WMM);
	else
		status = api->halmac_init_mac_cfg(halmac,
						  HALMAC_TRX_MODE_NORMAL);
	if (status != HALMAC_RET_SUCCESS)
		goto out;

	err = rtl_halmac_rx_agg_switch(rtlpriv, true);
	if (err)
		goto out;

	if (rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS7])
		status = api->halmac_cfg_operation_mode(
			halmac, HALMAC_WIRELESS_MODE_AC);
	else if (rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS7])
		status = api->halmac_cfg_operation_mode(halmac,
							HALMAC_WIRELESS_MODE_N);
	else if (rtlpriv->cfg->maps[RTL_RC_OFDM_RATE6M])
		status = api->halmac_cfg_operation_mode(halmac,
							HALMAC_WIRELESS_MODE_G);
	else
		status = api->halmac_cfg_operation_mode(halmac,
							HALMAC_WIRELESS_MODE_B);
	if (status != HALMAC_RET_SUCCESS)
		goto out;

out:
	return status;
}