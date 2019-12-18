#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct tid_ampdu_rx {int timeout; int ssn; int head_seq_num; int buf_size; int auto_seq; int started; int tid; int /*<<< orphan*/  last_rx; int /*<<< orphan*/  session_timer; struct sta_info* sta; scalar_t__ reorder_buf_filtered; scalar_t__ stored_mpdu_num; struct tid_ampdu_rx* reorder_time; struct tid_ampdu_rx* reorder_buf; int /*<<< orphan*/  reorder_timer; int /*<<< orphan*/  reorder_lock; } ;
struct TYPE_9__ {int cap; int /*<<< orphan*/  ht_supported; } ;
struct TYPE_8__ {scalar_t__ has_he; } ;
struct TYPE_11__ {int max_rx_aggregation_subframes; int /*<<< orphan*/  addr; TYPE_2__ ht_cap; TYPE_1__ he_cap; } ;
struct TYPE_10__ {scalar_t__* tid_rx_token; int /*<<< orphan*/  unexpected_agg; int /*<<< orphan*/  agg_session_valid; int /*<<< orphan*/ * tid_rx; int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_4__ sta; TYPE_3__ ampdu_mlme; TYPE_5__* sdata; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct ieee80211_ampdu_params {int tid; int amsdu; int timeout; int ssn; int buf_size; int /*<<< orphan*/  action; TYPE_4__* sta; } ;
struct ieee80211_addba_ext_ie {int dummy; } ;
struct TYPE_12__ {struct ieee80211_local* local; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_AMPDU_RX_START ; 
 int IEEE80211_FIRST_TSPEC_TSID ; 
 int IEEE80211_HT_CAP_DELAY_BA ; 
 int IEEE80211_MAX_AMPDU_BUF ; 
 int IEEE80211_MAX_AMPDU_BUF_HT ; 
 int /*<<< orphan*/  SUPPORTS_REORDERING_BUFFER ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  TU_TO_EXP_TIME (int) ; 
 int /*<<< orphan*/  WLAN_BACK_RECIPIENT ; 
 int WLAN_STATUS_INVALID_QOS_PARAM ; 
 int WLAN_STATUS_REQUEST_DECLINED ; 
 int WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_QOS ; 
 int /*<<< orphan*/  WLAN_STA_BLOCK_BA ; 
 int /*<<< orphan*/  ___ieee80211_stop_rx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct tid_ampdu_rx*) ; 
 int drv_ampdu_action (struct ieee80211_local*,TYPE_5__*,struct ieee80211_ampdu_params*) ; 
 int /*<<< orphan*/  ht_dbg (TYPE_5__*,char*,int,int,...) ; 
 int /*<<< orphan*/  ht_dbg_ratelimited (TYPE_5__*,char*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_addba_resp (struct sta_info*,int /*<<< orphan*/ ,int,scalar_t__,int,int,int,int,struct ieee80211_addba_ext_ie const*) ; 
 int /*<<< orphan*/  jiffies ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tid_ampdu_rx*) ; 
 struct tid_ampdu_rx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tid_ampdu_rx*) ; 
 struct tid_ampdu_rx* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta_rx_agg_reorder_timer_expired ; 
 int /*<<< orphan*/  sta_rx_agg_session_timer_expired ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ___ieee80211_start_rx_ba_session(struct sta_info *sta,
				      u8 dialog_token, u16 timeout,
				      u16 start_seq_num, u16 ba_policy, u16 tid,
				      u16 buf_size, bool tx, bool auto_seq,
				      const struct ieee80211_addba_ext_ie *addbaext)
{
	struct ieee80211_local *local = sta->sdata->local;
	struct tid_ampdu_rx *tid_agg_rx;
	struct ieee80211_ampdu_params params = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_RX_START,
		.tid = tid,
		.amsdu = false,
		.timeout = timeout,
		.ssn = start_seq_num,
	};
	int i, ret = -EOPNOTSUPP;
	u16 status = WLAN_STATUS_REQUEST_DECLINED;
	u16 max_buf_size;

	if (tid >= IEEE80211_FIRST_TSPEC_TSID) {
		ht_dbg(sta->sdata,
		       "STA %pM requests BA session on unsupported tid %d\n",
		       sta->sta.addr, tid);
		goto end;
	}

	if (!sta->sta.ht_cap.ht_supported) {
		ht_dbg(sta->sdata,
		       "STA %pM erroneously requests BA session on tid %d w/o QoS\n",
		       sta->sta.addr, tid);
		/* send a response anyway, it's an error case if we get here */
		goto end;
	}

	if (test_sta_flag(sta, WLAN_STA_BLOCK_BA)) {
		ht_dbg(sta->sdata,
		       "Suspend in progress - Denying ADDBA request (%pM tid %d)\n",
		       sta->sta.addr, tid);
		goto end;
	}

	if (sta->sta.he_cap.has_he)
		max_buf_size = IEEE80211_MAX_AMPDU_BUF;
	else
		max_buf_size = IEEE80211_MAX_AMPDU_BUF_HT;

	/* sanity check for incoming parameters:
	 * check if configuration can support the BA policy
	 * and if buffer size does not exceeds max value */
	/* XXX: check own ht delayed BA capability?? */
	if (((ba_policy != 1) &&
	     (!(sta->sta.ht_cap.cap & IEEE80211_HT_CAP_DELAY_BA))) ||
	    (buf_size > max_buf_size)) {
		status = WLAN_STATUS_INVALID_QOS_PARAM;
		ht_dbg_ratelimited(sta->sdata,
				   "AddBA Req with bad params from %pM on tid %u. policy %d, buffer size %d\n",
				   sta->sta.addr, tid, ba_policy, buf_size);
		goto end;
	}
	/* determine default buffer size */
	if (buf_size == 0)
		buf_size = max_buf_size;

	/* make sure the size doesn't exceed the maximum supported by the hw */
	if (buf_size > sta->sta.max_rx_aggregation_subframes)
		buf_size = sta->sta.max_rx_aggregation_subframes;
	params.buf_size = buf_size;

	ht_dbg(sta->sdata, "AddBA Req buf_size=%d for %pM\n",
	       buf_size, sta->sta.addr);

	/* examine state machine */
	lockdep_assert_held(&sta->ampdu_mlme.mtx);

	if (test_bit(tid, sta->ampdu_mlme.agg_session_valid)) {
		if (sta->ampdu_mlme.tid_rx_token[tid] == dialog_token) {
			struct tid_ampdu_rx *tid_rx;

			ht_dbg_ratelimited(sta->sdata,
					   "updated AddBA Req from %pM on tid %u\n",
					   sta->sta.addr, tid);
			/* We have no API to update the timeout value in the
			 * driver so reject the timeout update if the timeout
			 * changed. If if did not change, i.e., no real update,
			 * just reply with success.
			 */
			rcu_read_lock();
			tid_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
			if (tid_rx && tid_rx->timeout == timeout)
				status = WLAN_STATUS_SUCCESS;
			else
				status = WLAN_STATUS_REQUEST_DECLINED;
			rcu_read_unlock();
			goto end;
		}

		ht_dbg_ratelimited(sta->sdata,
				   "unexpected AddBA Req from %pM on tid %u\n",
				   sta->sta.addr, tid);

		/* delete existing Rx BA session on the same tid */
		___ieee80211_stop_rx_ba_session(sta, tid, WLAN_BACK_RECIPIENT,
						WLAN_STATUS_UNSPECIFIED_QOS,
						false);
	}

	if (ieee80211_hw_check(&local->hw, SUPPORTS_REORDERING_BUFFER)) {
		ret = drv_ampdu_action(local, sta->sdata, &params);
		ht_dbg(sta->sdata,
		       "Rx A-MPDU request on %pM tid %d result %d\n",
		       sta->sta.addr, tid, ret);
		if (!ret)
			status = WLAN_STATUS_SUCCESS;
		goto end;
	}

	/* prepare A-MPDU MLME for Rx aggregation */
	tid_agg_rx = kzalloc(sizeof(*tid_agg_rx), GFP_KERNEL);
	if (!tid_agg_rx)
		goto end;

	spin_lock_init(&tid_agg_rx->reorder_lock);

	/* rx timer */
	timer_setup(&tid_agg_rx->session_timer,
		    sta_rx_agg_session_timer_expired, TIMER_DEFERRABLE);

	/* rx reorder timer */
	timer_setup(&tid_agg_rx->reorder_timer,
		    sta_rx_agg_reorder_timer_expired, 0);

	/* prepare reordering buffer */
	tid_agg_rx->reorder_buf =
		kcalloc(buf_size, sizeof(struct sk_buff_head), GFP_KERNEL);
	tid_agg_rx->reorder_time =
		kcalloc(buf_size, sizeof(unsigned long), GFP_KERNEL);
	if (!tid_agg_rx->reorder_buf || !tid_agg_rx->reorder_time) {
		kfree(tid_agg_rx->reorder_buf);
		kfree(tid_agg_rx->reorder_time);
		kfree(tid_agg_rx);
		goto end;
	}

	for (i = 0; i < buf_size; i++)
		__skb_queue_head_init(&tid_agg_rx->reorder_buf[i]);

	ret = drv_ampdu_action(local, sta->sdata, &params);
	ht_dbg(sta->sdata, "Rx A-MPDU request on %pM tid %d result %d\n",
	       sta->sta.addr, tid, ret);
	if (ret) {
		kfree(tid_agg_rx->reorder_buf);
		kfree(tid_agg_rx->reorder_time);
		kfree(tid_agg_rx);
		goto end;
	}

	/* update data */
	tid_agg_rx->ssn = start_seq_num;
	tid_agg_rx->head_seq_num = start_seq_num;
	tid_agg_rx->buf_size = buf_size;
	tid_agg_rx->timeout = timeout;
	tid_agg_rx->stored_mpdu_num = 0;
	tid_agg_rx->auto_seq = auto_seq;
	tid_agg_rx->started = false;
	tid_agg_rx->reorder_buf_filtered = 0;
	tid_agg_rx->tid = tid;
	tid_agg_rx->sta = sta;
	status = WLAN_STATUS_SUCCESS;

	/* activate it for RX */
	rcu_assign_pointer(sta->ampdu_mlme.tid_rx[tid], tid_agg_rx);

	if (timeout) {
		mod_timer(&tid_agg_rx->session_timer, TU_TO_EXP_TIME(timeout));
		tid_agg_rx->last_rx = jiffies;
	}

end:
	if (status == WLAN_STATUS_SUCCESS) {
		__set_bit(tid, sta->ampdu_mlme.agg_session_valid);
		__clear_bit(tid, sta->ampdu_mlme.unexpected_agg);
		sta->ampdu_mlme.tid_rx_token[tid] = dialog_token;
	}

	if (tx)
		ieee80211_send_addba_resp(sta, sta->sta.addr, tid,
					  dialog_token, status, 1, buf_size,
					  timeout, addbaext);
}