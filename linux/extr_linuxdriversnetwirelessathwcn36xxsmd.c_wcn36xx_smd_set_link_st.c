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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_set_link_state_req_msg {int state; TYPE_1__ header; int /*<<< orphan*/  self_mac_addr; int /*<<< orphan*/  bssid; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
typedef  enum wcn36xx_hal_link_state { ____Placeholder_wcn36xx_hal_link_state } wcn36xx_hal_link_state ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_set_link_state_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_set_link_state_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_SET_LINK_ST_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_set_link_st(struct wcn36xx *wcn, const u8 *bssid,
			    const u8 *sta_mac,
			    enum wcn36xx_hal_link_state state)
{
	struct wcn36xx_hal_set_link_state_req_msg msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_LINK_ST_REQ);

	memcpy(&msg_body.bssid, bssid, ETH_ALEN);
	memcpy(&msg_body.self_mac_addr, sta_mac, ETH_ALEN);
	msg_body.state = state;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal set link state bssid %pM self_mac_addr %pM state %d\n",
		    msg_body.bssid, msg_body.self_mac_addr, msg_body.state);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_set_link_st failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_set_link_st response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}