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
struct wcn36xx_vif {scalar_t__ bss_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_delete_bss_req_msg {scalar_t__ bss_index; TYPE_1__ header; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_delete_bss_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_delete_bss_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 scalar_t__ WCN36XX_HAL_BSS_INVALID_IDX ; 
 int /*<<< orphan*/  WCN36XX_HAL_DELETE_BSS_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

int wcn36xx_smd_delete_bss(struct wcn36xx *wcn, struct ieee80211_vif *vif)
{
	struct wcn36xx_hal_delete_bss_req_msg msg_body;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	int ret = 0;

	mutex_lock(&wcn->hal_mutex);

	if (vif_priv->bss_index == WCN36XX_HAL_BSS_INVALID_IDX)
		goto out;

	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DELETE_BSS_REQ);

	msg_body.bss_index = vif_priv->bss_index;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal delete bss %d\n", msg_body.bss_index);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_delete_bss failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_delete_bss response failed err=%d\n", ret);
		goto out;
	}

	vif_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}