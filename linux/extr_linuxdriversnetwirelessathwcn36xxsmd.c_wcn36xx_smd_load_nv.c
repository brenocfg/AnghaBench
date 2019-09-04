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
typedef  int u16 ;
struct TYPE_3__ {int len; } ;
struct wcn36xx_hal_nv_img_download_req_msg {int last_fragment; int nv_img_buffer_size; scalar_t__ frag_number; TYPE_1__ header; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; scalar_t__ hal_buf; TYPE_2__* nv; int /*<<< orphan*/  dev; } ;
struct nv_data {struct wcn36xx_hal_nv_img_download_req_msg table; } ;
typedef  int /*<<< orphan*/  msg_body ;
struct TYPE_4__ {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_nv_img_download_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WCN36XX_HAL_DOWNLOAD_NV_REQ ; 
 int WCN36XX_NV_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  WLAN_NV_FILE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct wcn36xx_hal_nv_img_download_req_msg*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_firmware (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,int,...) ; 
 int wcn36xx_smd_rsp_status_check (scalar_t__,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int) ; 

int wcn36xx_smd_load_nv(struct wcn36xx *wcn)
{
	struct nv_data *nv_d;
	struct wcn36xx_hal_nv_img_download_req_msg msg_body;
	int fw_bytes_left;
	int ret;
	u16 fm_offset = 0;

	if (!wcn->nv) {
		ret = request_firmware(&wcn->nv, WLAN_NV_FILE, wcn->dev);
		if (ret) {
			wcn36xx_err("Failed to load nv file %s: %d\n",
				      WLAN_NV_FILE, ret);
			goto out;
		}
	}

	nv_d = (struct nv_data *)wcn->nv->data;
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DOWNLOAD_NV_REQ);

	msg_body.header.len += WCN36XX_NV_FRAGMENT_SIZE;

	msg_body.frag_number = 0;
	/* hal_buf must be protected with  mutex */
	mutex_lock(&wcn->hal_mutex);

	do {
		fw_bytes_left = wcn->nv->size - fm_offset - 4;
		if (fw_bytes_left > WCN36XX_NV_FRAGMENT_SIZE) {
			msg_body.last_fragment = 0;
			msg_body.nv_img_buffer_size = WCN36XX_NV_FRAGMENT_SIZE;
		} else {
			msg_body.last_fragment = 1;
			msg_body.nv_img_buffer_size = fw_bytes_left;

			/* Do not forget update general message len */
			msg_body.header.len = sizeof(msg_body) + fw_bytes_left;

		}

		/* Add load NV request message header */
		memcpy(wcn->hal_buf, &msg_body,	sizeof(msg_body));

		/* Add NV body itself */
		memcpy(wcn->hal_buf + sizeof(msg_body),
		       &nv_d->table + fm_offset,
		       msg_body.nv_img_buffer_size);

		ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
		if (ret)
			goto out_unlock;
		ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf,
						   wcn->hal_rsp_len);
		if (ret) {
			wcn36xx_err("hal_load_nv response failed err=%d\n",
				    ret);
			goto out_unlock;
		}
		msg_body.frag_number++;
		fm_offset += WCN36XX_NV_FRAGMENT_SIZE;

	} while (msg_body.last_fragment != 1);

out_unlock:
	mutex_unlock(&wcn->hal_mutex);
out:	return ret;
}