#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned long u16 ;
struct TYPE_4__ {int /*<<< orphan*/ * txq; } ;
struct sta_info {TYPE_2__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int priority; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned long BIT (int) ; 
 int IEEE80211_AC_VO ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREDATA ; 
 int IEEE80211_FRAME_RELEASE_PSPOLL ; 
 int IEEE80211_FRAME_RELEASE_UAPSD ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_QOS_CTL_EOSP ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int /*<<< orphan*/  IEEE80211_TX_CTRL_PS_RESPONSE ; 
 int IEEE80211_TX_STATUS_EOSP ; 
 int /*<<< orphan*/  WLAN_STA_SP ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_allow_buffered_frames (struct ieee80211_local*,struct sta_info*,unsigned long,int,int,int) ; 
 int /*<<< orphan*/  drv_release_buffered_frames (struct ieee80211_local*,struct sta_info*,unsigned long,int,int,int) ; 
 int find_highest_prio_tid (unsigned long) ; 
 int* ieee80211_ac_to_qos_mask ; 
 int /*<<< orphan*/  ieee80211_add_pending_skbs (struct ieee80211_local*,struct sk_buff_head*) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_null_response (struct sta_info*,int,int,int,int) ; 
 int /*<<< orphan*/  ieee80211_sta_ps_get_frames (struct sta_info*,int,int,int,struct sk_buff_head*,unsigned long*) ; 
 int ieee80211_sta_ps_more_data (struct sta_info*,int,int,unsigned long) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sta_info_recalc_tim (struct sta_info*) ; 
 scalar_t__ txq_has_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_sta_ps_deliver_response(struct sta_info *sta,
				  int n_frames, u8 ignored_acs,
				  enum ieee80211_frame_release_type reason)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	unsigned long driver_release_tids = 0;
	struct sk_buff_head frames;
	bool more_data;

	/* Service or PS-Poll period starts */
	set_sta_flag(sta, WLAN_STA_SP);

	__skb_queue_head_init(&frames);

	ieee80211_sta_ps_get_frames(sta, n_frames, ignored_acs, reason,
				    &frames, &driver_release_tids);

	more_data = ieee80211_sta_ps_more_data(sta, ignored_acs, reason, driver_release_tids);

	if (driver_release_tids && reason == IEEE80211_FRAME_RELEASE_PSPOLL)
		driver_release_tids =
			BIT(find_highest_prio_tid(driver_release_tids));

	if (skb_queue_empty(&frames) && !driver_release_tids) {
		int tid, ac;

		/*
		 * For PS-Poll, this can only happen due to a race condition
		 * when we set the TIM bit and the station notices it, but
		 * before it can poll for the frame we expire it.
		 *
		 * For uAPSD, this is said in the standard (11.2.1.5 h):
		 *	At each unscheduled SP for a non-AP STA, the AP shall
		 *	attempt to transmit at least one MSDU or MMPDU, but no
		 *	more than the value specified in the Max SP Length field
		 *	in the QoS Capability element from delivery-enabled ACs,
		 *	that are destined for the non-AP STA.
		 *
		 * Since we have no other MSDU/MMPDU, transmit a QoS null frame.
		 */

		/* This will evaluate to 1, 3, 5 or 7. */
		for (ac = IEEE80211_AC_VO; ac < IEEE80211_NUM_ACS; ac++)
			if (!(ignored_acs & ieee80211_ac_to_qos_mask[ac]))
				break;
		tid = 7 - 2 * ac;

		ieee80211_send_null_response(sta, tid, reason, true, false);
	} else if (!driver_release_tids) {
		struct sk_buff_head pending;
		struct sk_buff *skb;
		int num = 0;
		u16 tids = 0;
		bool need_null = false;

		skb_queue_head_init(&pending);

		while ((skb = __skb_dequeue(&frames))) {
			struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			struct ieee80211_hdr *hdr = (void *) skb->data;
			u8 *qoshdr = NULL;

			num++;

			/*
			 * Tell TX path to send this frame even though the
			 * STA may still remain is PS mode after this frame
			 * exchange.
			 */
			info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;
			info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;

			/*
			 * Use MoreData flag to indicate whether there are
			 * more buffered frames for this STA
			 */
			if (more_data || !skb_queue_empty(&frames))
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
			else
				hdr->frame_control &=
					cpu_to_le16(~IEEE80211_FCTL_MOREDATA);

			if (ieee80211_is_data_qos(hdr->frame_control) ||
			    ieee80211_is_qos_nullfunc(hdr->frame_control))
				qoshdr = ieee80211_get_qos_ctl(hdr);

			tids |= BIT(skb->priority);

			__skb_queue_tail(&pending, skb);

			/* end service period after last frame or add one */
			if (!skb_queue_empty(&frames))
				continue;

			if (reason != IEEE80211_FRAME_RELEASE_UAPSD) {
				/* for PS-Poll, there's only one frame */
				info->flags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTL_REQ_TX_STATUS;
				break;
			}

			/* For uAPSD, things are a bit more complicated. If the
			 * last frame has a QoS header (i.e. is a QoS-data or
			 * QoS-nulldata frame) then just set the EOSP bit there
			 * and be done.
			 * If the frame doesn't have a QoS header (which means
			 * it should be a bufferable MMPDU) then we can't set
			 * the EOSP bit in the QoS header; add a QoS-nulldata
			 * frame to the list to send it after the MMPDU.
			 *
			 * Note that this code is only in the mac80211-release
			 * code path, we assume that the driver will not buffer
			 * anything but QoS-data frames, or if it does, will
			 * create the QoS-nulldata frame by itself if needed.
			 *
			 * Cf. 802.11-2012 10.2.1.10 (c).
			 */
			if (qoshdr) {
				*qoshdr |= IEEE80211_QOS_CTL_EOSP;

				info->flags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTL_REQ_TX_STATUS;
			} else {
				/* The standard isn't completely clear on this
				 * as it says the more-data bit should be set
				 * if there are more BUs. The QoS-Null frame
				 * we're about to send isn't buffered yet, we
				 * only create it below, but let's pretend it
				 * was buffered just in case some clients only
				 * expect more-data=0 when eosp=1.
				 */
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
				need_null = true;
				num++;
			}
			break;
		}

		drv_allow_buffered_frames(local, sta, tids, num,
					  reason, more_data);

		ieee80211_add_pending_skbs(local, &pending);

		if (need_null)
			ieee80211_send_null_response(
				sta, find_highest_prio_tid(tids),
				reason, false, false);

		sta_info_recalc_tim(sta);
	} else {
		int tid;

		/*
		 * We need to release a frame that is buffered somewhere in the
		 * driver ... it'll have to handle that.
		 * Note that the driver also has to check the number of frames
		 * on the TIDs we're releasing from - if there are more than
		 * n_frames it has to set the more-data bit (if we didn't ask
		 * it to set it anyway due to other buffered frames); if there
		 * are fewer than n_frames it has to make sure to adjust that
		 * to allow the service period to end properly.
		 */
		drv_release_buffered_frames(local, sta, driver_release_tids,
					    n_frames, reason, more_data);

		/*
		 * Note that we don't recalculate the TIM bit here as it would
		 * most likely have no effect at all unless the driver told us
		 * that the TID(s) became empty before returning here from the
		 * release function.
		 * Either way, however, when the driver tells us that the TID(s)
		 * became empty or we find that a txq became empty, we'll do the
		 * TIM recalculation.
		 */

		if (!sta->sta.txq[0])
			return;

		for (tid = 0; tid < ARRAY_SIZE(sta->sta.txq); tid++) {
			if (!sta->sta.txq[tid] ||
			    !(driver_release_tids & BIT(tid)) ||
			    txq_has_queue(sta->sta.txq[tid]))
				continue;

			sta_info_recalc_tim(sta);
			break;
		}
	}
}