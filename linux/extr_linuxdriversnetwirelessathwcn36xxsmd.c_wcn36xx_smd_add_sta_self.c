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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_add_sta_self_req {TYPE_1__ header; int /*<<< orphan*/  status; int /*<<< orphan*/  self_addr; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_add_sta_self_req,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_add_sta_self_req) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_ADD_STA_SELF_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_add_sta_self_rsp (struct wcn36xx*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_add_sta_self(struct wcn36xx *wcn, struct ieee80211_vif *vif)
{
	struct wcn36xx_hal_add_sta_self_req msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ADD_STA_SELF_REQ);

	memcpy(&msg_body.self_addr, vif->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal add sta self self_addr %pM status %d\n",
		    msg_body.self_addr, msg_body.status);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_add_sta_self failed\n");
		goto out;
	}
	ret = wcn36xx_smd_add_sta_self_rsp(wcn,
					   vif,
					   wcn->hal_buf,
					   wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_add_sta_self response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}