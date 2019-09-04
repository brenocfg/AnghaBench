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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; struct ath6kl* ar; } ;
struct ath6kl_sta {int sta_flags; int /*<<< orphan*/  aid; int /*<<< orphan*/  psq_lock; int /*<<< orphan*/  psq; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int STA_PS_POLLED ; 
 int /*<<< orphan*/  WMI_DATA_HDR_FLAGS_MORE ; 
 int /*<<< orphan*/  ath6kl_wmi_set_pvb_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath6kl_process_psq(struct ath6kl_sta *conn,
				struct ath6kl_vif *vif,
				struct sk_buff *skb,
				u32 *flags)
{
	bool is_psq_empty = false;
	struct ath6kl *ar = vif->ar;

	if (conn->sta_flags & STA_PS_POLLED) {
		spin_lock_bh(&conn->psq_lock);
		if (!skb_queue_empty(&conn->psq))
			*flags |= WMI_DATA_HDR_FLAGS_MORE;
		spin_unlock_bh(&conn->psq_lock);
		return false;
	}

	/* Queue the frames if the STA is sleeping */
	spin_lock_bh(&conn->psq_lock);
	is_psq_empty = skb_queue_empty(&conn->psq);
	skb_queue_tail(&conn->psq, skb);
	spin_unlock_bh(&conn->psq_lock);

	/*
	 * If this is the first pkt getting queued
	 * for this STA, update the PVB for this
	 * STA.
	 */
	if (is_psq_empty)
		ath6kl_wmi_set_pvb_cmd(ar->wmi,
				       vif->fw_vif_idx,
				       conn->aid, 1);
	return true;
}