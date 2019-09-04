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
struct wcn36xx_hal_process_ptt_msg_req_msg {TYPE_1__ header; int /*<<< orphan*/  ptt_msg; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HAL_PTT_MSG (struct wcn36xx_hal_process_ptt_msg_req_msg*,size_t) ; 
 int /*<<< orphan*/  PREPARE_HAL_PTT_MSG_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_process_ptt_msg_req_msg*) ; 
 int /*<<< orphan*/  kfree (struct wcn36xx_hal_process_ptt_msg_req_msg*) ; 
 struct wcn36xx_hal_process_ptt_msg_req_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_process_ptt_msg_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_process_ptt_msg(struct wcn36xx *wcn,
				struct ieee80211_vif *vif, void *ptt_msg, size_t len,
		void **ptt_rsp_msg)
{
	struct wcn36xx_hal_process_ptt_msg_req_msg *p_msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	p_msg_body = kmalloc(
		sizeof(struct wcn36xx_hal_process_ptt_msg_req_msg) + len,
		GFP_ATOMIC);
	if (!p_msg_body) {
		ret = -ENOMEM;
		goto out_nomem;
	}
	INIT_HAL_PTT_MSG(p_msg_body, len);

	memcpy(&p_msg_body->ptt_msg, ptt_msg, len);

	PREPARE_HAL_PTT_MSG_BUF(wcn->hal_buf, p_msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, p_msg_body->header.len);
	if (ret) {
		wcn36xx_err("Sending hal_process_ptt_msg failed\n");
		goto out;
	}
	ret = wcn36xx_smd_process_ptt_msg_rsp(wcn->hal_buf, wcn->hal_rsp_len,
					      ptt_rsp_msg);
	if (ret) {
		wcn36xx_err("process_ptt_msg response failed err=%d\n", ret);
		goto out;
	}
out:
	kfree(p_msg_body);
out_nomem:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}