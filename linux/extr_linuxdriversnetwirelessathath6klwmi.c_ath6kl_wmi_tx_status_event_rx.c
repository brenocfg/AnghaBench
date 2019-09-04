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
struct wmi_tx_status_event {int /*<<< orphan*/  ack_status; int /*<<< orphan*/  id; } ;
struct wmi {int /*<<< orphan*/  last_mgmt_tx_frame_len; int /*<<< orphan*/ * last_mgmt_tx_frame; } ;
struct ath6kl_vif {int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_mgmt_tx_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_tx_status_event_rx(struct wmi *wmi, u8 *datap, int len,
					 struct ath6kl_vif *vif)
{
	struct wmi_tx_status_event *ev;
	u32 id;

	if (len < sizeof(*ev))
		return -EINVAL;

	ev = (struct wmi_tx_status_event *) datap;
	id = le32_to_cpu(ev->id);
	ath6kl_dbg(ATH6KL_DBG_WMI, "tx_status: id=%x ack_status=%u\n",
		   id, ev->ack_status);
	if (wmi->last_mgmt_tx_frame) {
		cfg80211_mgmt_tx_status(&vif->wdev, id,
					wmi->last_mgmt_tx_frame,
					wmi->last_mgmt_tx_frame_len,
					!!ev->ack_status, GFP_ATOMIC);
		kfree(wmi->last_mgmt_tx_frame);
		wmi->last_mgmt_tx_frame = NULL;
		wmi->last_mgmt_tx_frame_len = 0;
	}

	return 0;
}