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
struct wcn36xx_hal_feat_caps_msg {int /*<<< orphan*/ * feat_caps; TYPE_1__ header; } ;
struct wcn36xx {int hal_rsp_len; int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/ * fw_feat_caps; scalar_t__ hal_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_feat_caps_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (scalar_t__,struct wcn36xx_hal_feat_caps_msg) ; 
 int /*<<< orphan*/  STA_POWERSAVE ; 
 int WCN36XX_HAL_CAPS_SIZE ; 
 int /*<<< orphan*/  WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_feat_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_feature_caps_exchange(struct wcn36xx *wcn)
{
	struct wcn36xx_hal_feat_caps_msg msg_body, *rsp;
	int ret, i;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_REQ);

	set_feat_caps(msg_body.feat_caps, STA_POWERSAVE);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_feature_caps_exchange failed\n");
		goto out;
	}
	if (wcn->hal_rsp_len != sizeof(*rsp)) {
		wcn36xx_err("Invalid hal_feature_caps_exchange response");
		goto out;
	}

	rsp = (struct wcn36xx_hal_feat_caps_msg *) wcn->hal_buf;

	for (i = 0; i < WCN36XX_HAL_CAPS_SIZE; i++)
		wcn->fw_feat_caps[i] = rsp->feat_caps[i];
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}