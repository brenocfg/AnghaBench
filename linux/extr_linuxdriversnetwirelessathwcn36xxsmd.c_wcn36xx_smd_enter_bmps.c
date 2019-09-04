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
struct wcn36xx_vif {int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  bss_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_enter_bmps_req_msg {TYPE_2__ header; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  tbtt; int /*<<< orphan*/  bss_index; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  sync_tsf; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_enter_bmps_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_enter_bmps_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_HAL_ENTER_BMPS_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

int wcn36xx_smd_enter_bmps(struct wcn36xx *wcn, struct ieee80211_vif *vif)
{
	struct wcn36xx_hal_enter_bmps_req_msg msg_body;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ENTER_BMPS_REQ);

	msg_body.bss_index = vif_priv->bss_index;
	msg_body.tbtt = vif->bss_conf.sync_tsf;
	msg_body.dtim_period = vif_priv->dtim_period;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_enter_bmps failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_enter_bmps response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}