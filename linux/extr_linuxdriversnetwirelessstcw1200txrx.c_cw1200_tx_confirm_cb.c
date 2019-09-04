#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wsm_tx_confirm {scalar_t__ packet_id; scalar_t__ status; int ack_failures; int flags; } ;
struct wsm_suspend_resume {int link_id; int stop; int multicast; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_10__ {TYPE_4__* hw_key; } ;
struct TYPE_8__ {TYPE_2__* rates; } ;
struct ieee80211_tx_info {TYPE_5__ control; TYPE_3__ status; int /*<<< orphan*/  flags; } ;
struct cw1200_txpriv {int dummy; } ;
struct cw1200_queue {int dummy; } ;
struct cw1200_common {scalar_t__ mode; int buffered_multicasts; scalar_t__ bss_loss_confirm_id; int /*<<< orphan*/  bss_loss_lock; scalar_t__ bss_loss_state; int /*<<< orphan*/  ht_info; int /*<<< orphan*/  ps_state_lock; int /*<<< orphan*/  multicast_start_work; int /*<<< orphan*/  workqueue; scalar_t__ sta_asleep_mask; TYPE_1__* hw; struct cw1200_queue* tx_queue; } ;
struct TYPE_9__ {scalar_t__ cipher; scalar_t__ icv_len; } ;
struct TYPE_7__ {int count; int flags; int idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_MAX_RATES ; 
 size_t IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 scalar_t__ WSM_REQUEUE ; 
 int WSM_TX_STATUS_AGGREGATION ; 
 int WSM_TX_STATUS_REQUEUE ; 
 int /*<<< orphan*/  __cw1200_cqm_bssloss_sm (struct cw1200_common*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cw1200_bh_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_debug_txed (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_debug_txed_agg (struct cw1200_common*) ; 
 scalar_t__ cw1200_ht_greenfield (int /*<<< orphan*/ *) ; 
 scalar_t__ cw1200_queue_get_generation (scalar_t__) ; 
 size_t cw1200_queue_get_queue_id (scalar_t__) ; 
 int /*<<< orphan*/  cw1200_queue_get_skb (struct cw1200_queue*,scalar_t__,struct sk_buff**,struct cw1200_txpriv const**) ; 
 int /*<<< orphan*/  cw1200_queue_remove (struct cw1200_queue*,scalar_t__) ; 
 int /*<<< orphan*/  cw1200_queue_requeue (struct cw1200_queue*,scalar_t__) ; 
 int /*<<< orphan*/  cw1200_suspend_resume (struct cw1200_common*,struct wsm_suspend_resume*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_warn (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 

void cw1200_tx_confirm_cb(struct cw1200_common *priv,
			  int link_id,
			  struct wsm_tx_confirm *arg)
{
	u8 queue_id = cw1200_queue_get_queue_id(arg->packet_id);
	struct cw1200_queue *queue = &priv->tx_queue[queue_id];
	struct sk_buff *skb;
	const struct cw1200_txpriv *txpriv;

	pr_debug("[TX] TX confirm: %d, %d.\n",
		 arg->status, arg->ack_failures);

	if (priv->mode == NL80211_IFTYPE_UNSPECIFIED) {
		/* STA is stopped. */
		return;
	}

	if (WARN_ON(queue_id >= 4))
		return;

	if (arg->status)
		pr_debug("TX failed: %d.\n", arg->status);

	if ((arg->status == WSM_REQUEUE) &&
	    (arg->flags & WSM_TX_STATUS_REQUEUE)) {
		/* "Requeue" means "implicit suspend" */
		struct wsm_suspend_resume suspend = {
			.link_id = link_id,
			.stop = 1,
			.multicast = !link_id,
		};
		cw1200_suspend_resume(priv, &suspend);
		wiphy_warn(priv->hw->wiphy, "Requeue for link_id %d (try %d). STAs asleep: 0x%.8X\n",
			   link_id,
			   cw1200_queue_get_generation(arg->packet_id) + 1,
			   priv->sta_asleep_mask);
		cw1200_queue_requeue(queue, arg->packet_id);
		spin_lock_bh(&priv->ps_state_lock);
		if (!link_id) {
			priv->buffered_multicasts = true;
			if (priv->sta_asleep_mask) {
				queue_work(priv->workqueue,
					   &priv->multicast_start_work);
			}
		}
		spin_unlock_bh(&priv->ps_state_lock);
	} else if (!cw1200_queue_get_skb(queue, arg->packet_id,
					 &skb, &txpriv)) {
		struct ieee80211_tx_info *tx = IEEE80211_SKB_CB(skb);
		int tx_count = arg->ack_failures;
		u8 ht_flags = 0;
		int i;

		if (cw1200_ht_greenfield(&priv->ht_info))
			ht_flags |= IEEE80211_TX_RC_GREEN_FIELD;

		spin_lock(&priv->bss_loss_lock);
		if (priv->bss_loss_state &&
		    arg->packet_id == priv->bss_loss_confirm_id) {
			if (arg->status) {
				/* Recovery failed */
				__cw1200_cqm_bssloss_sm(priv, 0, 0, 1);
			} else {
				/* Recovery succeeded */
				__cw1200_cqm_bssloss_sm(priv, 0, 1, 0);
			}
		}
		spin_unlock(&priv->bss_loss_lock);

		if (!arg->status) {
			tx->flags |= IEEE80211_TX_STAT_ACK;
			++tx_count;
			cw1200_debug_txed(priv);
			if (arg->flags & WSM_TX_STATUS_AGGREGATION) {
				/* Do not report aggregation to mac80211:
				 * it confuses minstrel a lot.
				 */
				/* tx->flags |= IEEE80211_TX_STAT_AMPDU; */
				cw1200_debug_txed_agg(priv);
			}
		} else {
			if (tx_count)
				++tx_count;
		}

		for (i = 0; i < IEEE80211_TX_MAX_RATES; ++i) {
			if (tx->status.rates[i].count >= tx_count) {
				tx->status.rates[i].count = tx_count;
				break;
			}
			tx_count -= tx->status.rates[i].count;
			if (tx->status.rates[i].flags & IEEE80211_TX_RC_MCS)
				tx->status.rates[i].flags |= ht_flags;
		}

		for (++i; i < IEEE80211_TX_MAX_RATES; ++i) {
			tx->status.rates[i].count = 0;
			tx->status.rates[i].idx = -1;
		}

		/* Pull off any crypto trailers that we added on */
		if (tx->control.hw_key) {
			skb_trim(skb, skb->len - tx->control.hw_key->icv_len);
			if (tx->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP)
				skb_trim(skb, skb->len - 8); /* MIC space */
		}
		cw1200_queue_remove(queue, arg->packet_id);
	}
	/* XXX TODO:  Only wake if there are pending transmits.. */
	cw1200_bh_wakeup(priv);
}