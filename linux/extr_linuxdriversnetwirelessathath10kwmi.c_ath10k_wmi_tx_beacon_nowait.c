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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k_vif {int beacon_state; int /*<<< orphan*/  vdev_id; struct ath10k* ar; struct sk_buff* beacon; } ;
struct ath10k_skb_cb {int flags; int /*<<< orphan*/  paddr; } ;
struct ath10k {int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
#define  ATH10K_BEACON_SCHEDULED 130 
#define  ATH10K_BEACON_SENDING 129 
#define  ATH10K_BEACON_SENT 128 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int ATH10K_SKB_F_DELIVER_CAB ; 
 int ATH10K_SKB_F_DTIM_ZERO ; 
 int ath10k_wmi_beacon_send_ref_nowait (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_wmi_tx_beacon_nowait(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	struct ath10k_skb_cb *cb;
	struct sk_buff *bcn;
	bool dtim_zero;
	bool deliver_cab;
	int ret;

	spin_lock_bh(&ar->data_lock);

	bcn = arvif->beacon;

	if (!bcn)
		goto unlock;

	cb = ATH10K_SKB_CB(bcn);

	switch (arvif->beacon_state) {
	case ATH10K_BEACON_SENDING:
	case ATH10K_BEACON_SENT:
		break;
	case ATH10K_BEACON_SCHEDULED:
		arvif->beacon_state = ATH10K_BEACON_SENDING;
		spin_unlock_bh(&ar->data_lock);

		dtim_zero = !!(cb->flags & ATH10K_SKB_F_DTIM_ZERO);
		deliver_cab = !!(cb->flags & ATH10K_SKB_F_DELIVER_CAB);
		ret = ath10k_wmi_beacon_send_ref_nowait(arvif->ar,
							arvif->vdev_id,
							bcn->data, bcn->len,
							cb->paddr,
							dtim_zero,
							deliver_cab);

		spin_lock_bh(&ar->data_lock);

		if (ret == 0)
			arvif->beacon_state = ATH10K_BEACON_SENT;
		else
			arvif->beacon_state = ATH10K_BEACON_SCHEDULED;
	}

unlock:
	spin_unlock_bh(&ar->data_lock);
}