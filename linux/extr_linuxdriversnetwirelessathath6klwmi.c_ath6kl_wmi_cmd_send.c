#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct wmi_cmd_hdr {void* info1; void* cmd_id; } ;
struct wmi {int ep_id; TYPE_1__* parent_dev; } ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
typedef  enum wmi_sync_flag { ____Placeholder_wmi_sync_flag } wmi_sync_flag ;
typedef  enum wmi_cmd_id { ____Placeholder_wmi_cmd_id } wmi_cmd_id ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
struct TYPE_3__ {int vif_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int /*<<< orphan*/  ATH6KL_DBG_WMI_DUMP ; 
 int EINVAL ; 
 int END_WMIFLAG ; 
 int /*<<< orphan*/  OPT_MSGTYPE ; 
 int SYNC_AFTER_WMIFLAG ; 
 int SYNC_BEFORE_WMIFLAG ; 
 int SYNC_BOTH_WMIFLAG ; 
 scalar_t__ WARN_ON (int) ; 
 int WMI_CMD_HDR_IF_ID_MASK ; 
 int WMI_OPT_TX_FRAME_CMDID ; 
 int /*<<< orphan*/  WMM_AC_BE ; 
 int ath6kl_ac2_endpoint_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_control_tx (TYPE_1__*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath6kl_dbg_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_data_hdr_add (struct wmi*,struct sk_buff*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath6kl_wmi_sync_point (struct wmi*,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

int ath6kl_wmi_cmd_send(struct wmi *wmi, u8 if_idx, struct sk_buff *skb,
			enum wmi_cmd_id cmd_id, enum wmi_sync_flag sync_flag)
{
	struct wmi_cmd_hdr *cmd_hdr;
	enum htc_endpoint_id ep_id = wmi->ep_id;
	int ret;
	u16 info1;

	if (WARN_ON(skb == NULL ||
		    (if_idx > (wmi->parent_dev->vif_max - 1)))) {
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	ath6kl_dbg(ATH6KL_DBG_WMI, "wmi tx id %d len %d flag %d\n",
		   cmd_id, skb->len, sync_flag);
	ath6kl_dbg_dump(ATH6KL_DBG_WMI_DUMP, NULL, "wmi tx ",
			skb->data, skb->len);

	if (sync_flag >= END_WMIFLAG) {
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	if ((sync_flag == SYNC_BEFORE_WMIFLAG) ||
	    (sync_flag == SYNC_BOTH_WMIFLAG)) {
		/*
		 * Make sure all data currently queued is transmitted before
		 * the cmd execution.  Establish a new sync point.
		 */
		ath6kl_wmi_sync_point(wmi, if_idx);
	}

	skb_push(skb, sizeof(struct wmi_cmd_hdr));

	cmd_hdr = (struct wmi_cmd_hdr *) skb->data;
	cmd_hdr->cmd_id = cpu_to_le16(cmd_id);
	info1 = if_idx & WMI_CMD_HDR_IF_ID_MASK;
	cmd_hdr->info1 = cpu_to_le16(info1);

	/* Only for OPT_TX_CMD, use BE endpoint. */
	if (cmd_id == WMI_OPT_TX_FRAME_CMDID) {
		ret = ath6kl_wmi_data_hdr_add(wmi, skb, OPT_MSGTYPE,
					      false, false, 0, NULL, if_idx);
		if (ret) {
			dev_kfree_skb(skb);
			return ret;
		}
		ep_id = ath6kl_ac2_endpoint_id(wmi->parent_dev, WMM_AC_BE);
	}

	ath6kl_control_tx(wmi->parent_dev, skb, ep_id);

	if ((sync_flag == SYNC_AFTER_WMIFLAG) ||
	    (sync_flag == SYNC_BOTH_WMIFLAG)) {
		/*
		 * Make sure all new data queued waits for the command to
		 * execute. Establish a new sync point.
		 */
		ath6kl_wmi_sync_point(wmi, if_idx);
	}

	return 0;
}