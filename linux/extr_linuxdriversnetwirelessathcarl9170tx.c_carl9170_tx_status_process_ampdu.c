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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_7__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ status; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int dummy; } ;
struct carl9170_sta_tid {scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct carl9170_sta_info {TYPE_5__* stats; int /*<<< orphan*/ * agg; } ;
struct ar9170 {int dummy; } ;
struct TYPE_9__ {scalar_t__ cnt; scalar_t__ rix; } ;
struct TYPE_8__ {int mac_control; } ;
struct _carl9170_tx_superframe {TYPE_4__ s; TYPE_3__ f; scalar_t__ frame_data; } ;
struct TYPE_10__ {int clear; int req; scalar_t__ ampdu_ack_len; scalar_t__ ampdu_len; } ;
struct TYPE_6__ {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_TX_MAC_IMM_BA ; 
 scalar_t__ CARL9170_TID_STATE_IDLE ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_INJECTED ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int IEEE80211_TX_STAT_AMPDU_NO_BACK ; 
 struct ieee80211_sta* __carl9170_get_tx_sta (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_tx_shift_bm (struct ar9170*,struct carl9170_sta_tid*,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_seq_h (struct ieee80211_hdr*) ; 
 size_t get_tid_h (struct ieee80211_hdr*) ; 
 scalar_t__ likely (int) ; 
 struct carl9170_sta_tid* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void carl9170_tx_status_process_ampdu(struct ar9170 *ar,
	struct sk_buff *skb, struct ieee80211_tx_info *txinfo)
{
	struct _carl9170_tx_superframe *super = (void *) skb->data;
	struct ieee80211_hdr *hdr = (void *) super->frame_data;
	struct ieee80211_sta *sta;
	struct carl9170_sta_info *sta_info;
	struct carl9170_sta_tid *tid_info;
	u8 tid;

	if (!(txinfo->flags & IEEE80211_TX_CTL_AMPDU) ||
	    txinfo->flags & IEEE80211_TX_CTL_INJECTED)
		return;

	rcu_read_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	if (unlikely(!sta))
		goto out_rcu;

	tid = get_tid_h(hdr);

	sta_info = (void *) sta->drv_priv;
	tid_info = rcu_dereference(sta_info->agg[tid]);
	if (!tid_info)
		goto out_rcu;

	spin_lock_bh(&tid_info->lock);
	if (likely(tid_info->state >= CARL9170_TID_STATE_IDLE))
		carl9170_tx_shift_bm(ar, tid_info, get_seq_h(hdr));

	if (sta_info->stats[tid].clear) {
		sta_info->stats[tid].clear = false;
		sta_info->stats[tid].req = false;
		sta_info->stats[tid].ampdu_len = 0;
		sta_info->stats[tid].ampdu_ack_len = 0;
	}

	sta_info->stats[tid].ampdu_len++;
	if (txinfo->status.rates[0].count == 1)
		sta_info->stats[tid].ampdu_ack_len++;

	if (!(txinfo->flags & IEEE80211_TX_STAT_ACK))
		sta_info->stats[tid].req = true;

	if (super->f.mac_control & cpu_to_le16(AR9170_TX_MAC_IMM_BA)) {
		super->s.rix = sta_info->stats[tid].ampdu_len;
		super->s.cnt = sta_info->stats[tid].ampdu_ack_len;
		txinfo->flags |= IEEE80211_TX_STAT_AMPDU;
		if (sta_info->stats[tid].req)
			txinfo->flags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;

		sta_info->stats[tid].clear = true;
	}
	spin_unlock_bh(&tid_info->lock);

out_rcu:
	rcu_read_unlock();
}