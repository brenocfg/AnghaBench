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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi {struct ath6kl* parent_dev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX ; 
 int __ath6kl_wmi_send_mgmt_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_send_action_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath6kl_wmi_send_mgmt_cmd(struct wmi *wmi, u8 if_idx, u32 id, u32 freq,
				u32 wait, const u8 *data, u16 data_len,
				u32 no_cck)
{
	int status;
	struct ath6kl *ar = wmi->parent_dev;

	if (test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		     ar->fw_capabilities)) {
		/*
		 * If capable of doing P2P mgmt operations using
		 * station interface, send additional information like
		 * supported rates to advertise and xmit rates for
		 * probe requests
		 */
		status = __ath6kl_wmi_send_mgmt_cmd(ar->wmi, if_idx, id, freq,
						    wait, data, data_len,
						    no_cck);
	} else {
		status = ath6kl_wmi_send_action_cmd(ar->wmi, if_idx, id, freq,
						    wait, data, data_len);
	}

	return status;
}