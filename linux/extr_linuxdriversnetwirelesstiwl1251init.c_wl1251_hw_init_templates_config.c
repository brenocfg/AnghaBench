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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_qos_null_data_template {int dummy; } ;
struct wl12xx_ps_poll_template {int dummy; } ;
struct wl12xx_probe_resp_template {int dummy; } ;
struct wl12xx_probe_req_template {int dummy; } ;
struct wl12xx_null_data_template {int dummy; } ;
struct wl12xx_beacon_template {int dummy; } ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_BEACON ; 
 int /*<<< orphan*/  CMD_NULL_DATA ; 
 int /*<<< orphan*/  CMD_PROBE_REQ ; 
 int /*<<< orphan*/  CMD_PROBE_RESP ; 
 int /*<<< orphan*/  CMD_PS_POLL ; 
 int /*<<< orphan*/  CMD_QOS_NULL_DATA ; 
 int PARTIAL_VBM_MAX ; 
 int /*<<< orphan*/  TIM_ELE_ID ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int wl1251_cmd_template_set (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int wl1251_cmd_vbm (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int wl1251_hw_init_templates_config(struct wl1251 *wl)
{
	int ret;
	u8 partial_vbm[PARTIAL_VBM_MAX];

	/* send empty templates for fw memory reservation */
	ret = wl1251_cmd_template_set(wl, CMD_PROBE_REQ, NULL,
				      sizeof(struct wl12xx_probe_req_template));
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_template_set(wl, CMD_NULL_DATA, NULL,
				      sizeof(struct wl12xx_null_data_template));
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_template_set(wl, CMD_PS_POLL, NULL,
				      sizeof(struct wl12xx_ps_poll_template));
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_template_set(wl, CMD_QOS_NULL_DATA, NULL,
				      sizeof
				      (struct wl12xx_qos_null_data_template));
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_template_set(wl, CMD_PROBE_RESP, NULL,
				      sizeof
				      (struct wl12xx_probe_resp_template));
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_template_set(wl, CMD_BEACON, NULL,
				      sizeof
				      (struct wl12xx_beacon_template));
	if (ret < 0)
		return ret;

	/* tim templates, first reserve space then allocate an empty one */
	memset(partial_vbm, 0, PARTIAL_VBM_MAX);
	ret = wl1251_cmd_vbm(wl, TIM_ELE_ID, partial_vbm, PARTIAL_VBM_MAX, 0);
	if (ret < 0)
		return ret;

	ret = wl1251_cmd_vbm(wl, TIM_ELE_ID, partial_vbm, 1, 0);
	if (ret < 0)
		return ret;

	return 0;
}