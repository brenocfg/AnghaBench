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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  ndev; struct ath6kl* ar; } ;
struct ath6kl_sta {int apsd_info; int /*<<< orphan*/  aid; int /*<<< orphan*/  sta_flags; int /*<<< orphan*/  psq_lock; int /*<<< orphan*/  apsdq; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int ATH6KL_APSD_ALL_FRAME ; 
 int ATH6KL_APSD_FRAME_MASK ; 
 int ATH6KL_APSD_NUM_OF_AC ; 
 int /*<<< orphan*/  STA_PS_APSD_EOSP ; 
 int /*<<< orphan*/  STA_PS_APSD_TRIGGER ; 
 int WMI_AP_APSD_NO_DELIVERY_FRAMES ; 
 int /*<<< orphan*/  ath6kl_data_tx (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_apsd_bfrd_traf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_uapsd_trigger_frame_rx(struct ath6kl_vif *vif,
						 struct ath6kl_sta *conn)
{
	struct ath6kl *ar = vif->ar;
	bool is_apsdq_empty, is_apsdq_empty_at_start;
	u32 num_frames_to_deliver, flags;
	struct sk_buff *skb = NULL;

	/*
	 * If the APSD q for this STA is not empty, dequeue and
	 * send a pkt from the head of the q. Also update the
	 * More data bit in the WMI_DATA_HDR if there are
	 * more pkts for this STA in the APSD q.
	 * If there are no more pkts for this STA,
	 * update the APSD bitmap for this STA.
	 */

	num_frames_to_deliver = (conn->apsd_info >> ATH6KL_APSD_NUM_OF_AC) &
						    ATH6KL_APSD_FRAME_MASK;
	/*
	 * Number of frames to send in a service period is
	 * indicated by the station
	 * in the QOS_INFO of the association request
	 * If it is zero, send all frames
	 */
	if (!num_frames_to_deliver)
		num_frames_to_deliver = ATH6KL_APSD_ALL_FRAME;

	spin_lock_bh(&conn->psq_lock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	spin_unlock_bh(&conn->psq_lock);
	is_apsdq_empty_at_start = is_apsdq_empty;

	while ((!is_apsdq_empty) && (num_frames_to_deliver)) {
		spin_lock_bh(&conn->psq_lock);
		skb = skb_dequeue(&conn->apsdq);
		is_apsdq_empty = skb_queue_empty(&conn->apsdq);
		spin_unlock_bh(&conn->psq_lock);

		/*
		 * Set the STA flag to Trigger delivery,
		 * so that the frame will go out
		 */
		conn->sta_flags |= STA_PS_APSD_TRIGGER;
		num_frames_to_deliver--;

		/* Last frame in the service period, set EOSP or queue empty */
		if ((is_apsdq_empty) || (!num_frames_to_deliver))
			conn->sta_flags |= STA_PS_APSD_EOSP;

		ath6kl_data_tx(skb, vif->ndev);
		conn->sta_flags &= ~(STA_PS_APSD_TRIGGER);
		conn->sta_flags &= ~(STA_PS_APSD_EOSP);
	}

	if (is_apsdq_empty) {
		if (is_apsdq_empty_at_start)
			flags = WMI_AP_APSD_NO_DELIVERY_FRAMES;
		else
			flags = 0;

		ath6kl_wmi_set_apsd_bfrd_traf(ar->wmi,
					      vif->fw_vif_idx,
					      conn->aid, 0, flags);
	}

	return;
}