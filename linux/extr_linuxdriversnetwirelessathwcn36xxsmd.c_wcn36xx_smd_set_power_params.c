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
struct wcn36xx_hal_set_power_params_req_msg {int ignore_dtim; int dtim_period; TYPE_1__ header; int /*<<< orphan*/  listen_interval; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_set_power_params_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_set_power_params_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_HAL_SET_POWER_PARAMS_REQ ; 
 int /*<<< orphan*/  WCN36XX_LISTEN_INTERVAL (struct wcn36xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_set_power_params(struct wcn36xx *wcn, bool ignore_dtim)
{
	struct wcn36xx_hal_set_power_params_req_msg msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_POWER_PARAMS_REQ);

	/*
	 * When host is down ignore every second dtim
	 */
	if (ignore_dtim) {
		msg_body.ignore_dtim = 1;
		msg_body.dtim_period = 2;
	}
	msg_body.listen_interval = WCN36XX_LISTEN_INTERVAL(wcn);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_set_power_params failed\n");
		goto out;
	}

out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}