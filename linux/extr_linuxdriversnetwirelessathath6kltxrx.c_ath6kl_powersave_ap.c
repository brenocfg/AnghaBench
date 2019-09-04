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
typedef  size_t u8 ;
typedef  int u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; struct ath6kl* ar; } ;
struct ath6kl_sta {int sta_flags; } ;
struct ath6kl {int /*<<< orphan*/  mcastpsq_lock; int /*<<< orphan*/  mcastpsq; int /*<<< orphan*/  wmi; TYPE_1__* sta_list; } ;
struct TYPE_2__ {int sta_flags; } ;

/* Variables and functions */
 size_t AP_MAX_NUM_STA ; 
 int /*<<< orphan*/  DTIM_EXPIRED ; 
 int /*<<< orphan*/  MCAST_AID ; 
 int STA_PS_SLEEP ; 
 int WMI_DATA_HDR_FLAGS_MORE ; 
 int WMI_DATA_HDR_FLAGS_UAPSD ; 
 struct ath6kl_sta* ath6kl_find_sta (struct ath6kl_vif*,int /*<<< orphan*/ ) ; 
 int ath6kl_process_psq (struct ath6kl_sta*,struct ath6kl_vif*,struct sk_buff*,int*) ; 
 int ath6kl_process_uapsdq (struct ath6kl_sta*,struct ath6kl_vif*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_pvb_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath6kl_powersave_ap(struct ath6kl_vif *vif, struct sk_buff *skb,
				u32 *flags)
{
	struct ethhdr *datap = (struct ethhdr *) skb->data;
	struct ath6kl_sta *conn = NULL;
	bool ps_queued = false;
	struct ath6kl *ar = vif->ar;

	if (is_multicast_ether_addr(datap->h_dest)) {
		u8 ctr = 0;
		bool q_mcast = false;

		for (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) {
			if (ar->sta_list[ctr].sta_flags & STA_PS_SLEEP) {
				q_mcast = true;
				break;
			}
		}

		if (q_mcast) {
			/*
			 * If this transmit is not because of a Dtim Expiry
			 * q it.
			 */
			if (!test_bit(DTIM_EXPIRED, &vif->flags)) {
				bool is_mcastq_empty = false;

				spin_lock_bh(&ar->mcastpsq_lock);
				is_mcastq_empty =
					skb_queue_empty(&ar->mcastpsq);
				skb_queue_tail(&ar->mcastpsq, skb);
				spin_unlock_bh(&ar->mcastpsq_lock);

				/*
				 * If this is the first Mcast pkt getting
				 * queued indicate to the target to set the
				 * BitmapControl LSB of the TIM IE.
				 */
				if (is_mcastq_empty)
					ath6kl_wmi_set_pvb_cmd(ar->wmi,
							       vif->fw_vif_idx,
							       MCAST_AID, 1);

				ps_queued = true;
			} else {
				/*
				 * This transmit is because of Dtim expiry.
				 * Determine if MoreData bit has to be set.
				 */
				spin_lock_bh(&ar->mcastpsq_lock);
				if (!skb_queue_empty(&ar->mcastpsq))
					*flags |= WMI_DATA_HDR_FLAGS_MORE;
				spin_unlock_bh(&ar->mcastpsq_lock);
			}
		}
	} else {
		conn = ath6kl_find_sta(vif, datap->h_dest);
		if (!conn) {
			dev_kfree_skb(skb);

			/* Inform the caller that the skb is consumed */
			return true;
		}

		if (conn->sta_flags & STA_PS_SLEEP) {
			ps_queued = ath6kl_process_uapsdq(conn,
						vif, skb, flags);
			if (!(*flags & WMI_DATA_HDR_FLAGS_UAPSD))
				ps_queued = ath6kl_process_psq(conn,
						vif, skb, flags);
		}
	}
	return ps_queued;
}