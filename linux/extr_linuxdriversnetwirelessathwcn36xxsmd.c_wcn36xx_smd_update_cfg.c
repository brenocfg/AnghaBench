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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t len; } ;
struct wcn36xx_hal_update_cfg_req_msg {size_t len; TYPE_1__ header; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; scalar_t__ hal_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_update_cfg_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (scalar_t__,struct wcn36xx_hal_update_cfg_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_HAL_UPDATE_CFG_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cfg_tlv_u32 (struct wcn36xx*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (scalar_t__,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,size_t) ; 

int wcn36xx_smd_update_cfg(struct wcn36xx *wcn, u32 cfg_id, u32 value)
{
	struct wcn36xx_hal_update_cfg_req_msg msg_body, *body;
	size_t len;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_UPDATE_CFG_REQ);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	body = (struct wcn36xx_hal_update_cfg_req_msg *) wcn->hal_buf;
	len = msg_body.header.len;

	put_cfg_tlv_u32(wcn, &len, cfg_id, value);
	body->header.len = len;
	body->len = len - sizeof(*body);

	ret = wcn36xx_smd_send_and_wait(wcn, body->header.len);
	if (ret) {
		wcn36xx_err("Sending hal_update_cfg failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_update_cfg response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}