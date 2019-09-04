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
struct wcn36xx_sta {int /*<<< orphan*/  ucast_dpu_sign; int /*<<< orphan*/  dpu_desc_index; int /*<<< orphan*/  sta_index; } ;
struct config_sta_rsp_params {scalar_t__ status; int /*<<< orphan*/  p2p; int /*<<< orphan*/  uc_ucast_sig; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  dpu_index; } ;
struct wcn36xx_hal_config_sta_rsp_msg {struct config_sta_rsp_params params; } ;
struct wcn36xx {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 scalar_t__ WCN36XX_FW_MSG_RESULT_SUCCESS ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,scalar_t__) ; 

__attribute__((used)) static int wcn36xx_smd_config_sta_rsp(struct wcn36xx *wcn,
				      struct ieee80211_sta *sta,
				      void *buf,
				      size_t len)
{
	struct wcn36xx_hal_config_sta_rsp_msg *rsp;
	struct config_sta_rsp_params *params;
	struct wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);

	if (len < sizeof(*rsp))
		return -EINVAL;

	rsp = (struct wcn36xx_hal_config_sta_rsp_msg *)buf;
	params = &rsp->params;

	if (params->status != WCN36XX_FW_MSG_RESULT_SUCCESS) {
		wcn36xx_warn("hal config sta response failure: %d\n",
			     params->status);
		return -EIO;
	}

	sta_priv->sta_index = params->sta_index;
	sta_priv->dpu_desc_index = params->dpu_index;
	sta_priv->ucast_dpu_sign = params->uc_ucast_sig;

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config sta rsp status %d sta_index %d bssid_index %d uc_ucast_sig %d p2p %d\n",
		    params->status, params->sta_index, params->bssid_index,
		    params->uc_ucast_sig, params->p2p);

	return 0;
}