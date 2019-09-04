#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int flags; int tx_bytes; int /*<<< orphan*/  users; scalar_t__ crypt; int /*<<< orphan*/  last_tx; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  aid; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  addr; } ;
struct sk_buff {int len; scalar_t__ data; scalar_t__ cb; } ;
struct ieee80211_hdr {int* addr1; int /*<<< orphan*/  frame_control; } ;
struct hostap_tx_data {struct sta_info* sta_ptr; scalar_t__ crypt; scalar_t__ host_encrypt; struct sk_buff* skb; } ;
struct hostap_skb_tx_data {int flags; int /*<<< orphan*/  rate; TYPE_1__* iface; } ;
struct TYPE_8__ {scalar_t__ iw_mode; TYPE_5__* dev; TYPE_6__* ap; int /*<<< orphan*/  fw_tx_rate_control; } ;
typedef  TYPE_2__ local_info_t ;
typedef  int ap_tx_ret ;
struct TYPE_10__ {scalar_t__ num_sta; int /*<<< orphan*/  last_tx_rate; int /*<<< orphan*/  tx_drop_nonassoc; int /*<<< orphan*/  sta_table_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ type; } ;

/* Variables and functions */
 int AP_TX_BUFFERED ; 
 int AP_TX_CONTINUE ; 
 int AP_TX_CONTINUE_NOT_AUTHORIZED ; 
 int AP_TX_DROP ; 
 int /*<<< orphan*/  DEBUG_PS ; 
 int /*<<< orphan*/  DEBUG_PS2 ; 
 scalar_t__ HOSTAP_INTERFACE_AP ; 
 scalar_t__ HOSTAP_INTERFACE_MASTER ; 
 scalar_t__ HOSTAP_INTERFACE_STA ; 
 int HOSTAP_TX_FLAGS_ADD_MOREDATA ; 
 int HOSTAP_TX_FLAGS_BUFFERED_FRAME ; 
 int HOSTAP_TX_FLAGS_WDS ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREDATA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ STA_MAX_TX_BUFFER ; 
 int WLAN_STA_AUTHORIZED ; 
 int WLAN_STA_PS ; 
 int WLAN_STA_TIM ; 
 struct sta_info* ap_get_sta (TYPE_6__*,int*) ; 
 int /*<<< orphan*/  ap_update_sta_tx_rate (struct sta_info*,TYPE_5__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_set_tim (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

ap_tx_ret hostap_handle_sta_tx(local_info_t *local, struct hostap_tx_data *tx)
{
	struct sta_info *sta = NULL;
	struct sk_buff *skb = tx->skb;
	int set_tim, ret;
	struct ieee80211_hdr *hdr;
	struct hostap_skb_tx_data *meta;

	meta = (struct hostap_skb_tx_data *) skb->cb;
	ret = AP_TX_CONTINUE;
	if (local->ap == NULL || skb->len < 10 ||
	    meta->iface->type == HOSTAP_INTERFACE_STA)
		goto out;

	hdr = (struct ieee80211_hdr *) skb->data;

	if (hdr->addr1[0] & 0x01) {
		/* broadcast/multicast frame - no AP related processing */
		if (local->ap->num_sta <= 0)
			ret = AP_TX_DROP;
		goto out;
	}

	/* unicast packet - check whether destination STA is associated */
	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr1);
	if (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	if (local->iw_mode == IW_MODE_MASTER && sta == NULL &&
	    !(meta->flags & HOSTAP_TX_FLAGS_WDS) &&
	    meta->iface->type != HOSTAP_INTERFACE_MASTER &&
	    meta->iface->type != HOSTAP_INTERFACE_AP) {
#if 0
		/* This can happen, e.g., when wlan0 is added to a bridge and
		 * bridging code does not know which port is the correct target
		 * for a unicast frame. In this case, the packet is send to all
		 * ports of the bridge. Since this is a valid scenario, do not
		 * print out any errors here. */
		if (net_ratelimit()) {
			printk(KERN_DEBUG "AP: drop packet to non-associated "
			       "STA %pM\n", hdr->addr1);
		}
#endif
		local->ap->tx_drop_nonassoc++;
		ret = AP_TX_DROP;
		goto out;
	}

	if (sta == NULL)
		goto out;

	if (!(sta->flags & WLAN_STA_AUTHORIZED))
		ret = AP_TX_CONTINUE_NOT_AUTHORIZED;

	/* Set tx_rate if using host-based TX rate control */
	if (!local->fw_tx_rate_control)
		local->ap->last_tx_rate = meta->rate =
			ap_update_sta_tx_rate(sta, local->dev);

	if (local->iw_mode != IW_MODE_MASTER)
		goto out;

	if (!(sta->flags & WLAN_STA_PS))
		goto out;

	if (meta->flags & HOSTAP_TX_FLAGS_ADD_MOREDATA) {
		/* indicate to STA that more frames follow */
		hdr->frame_control |=
			cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	}

	if (meta->flags & HOSTAP_TX_FLAGS_BUFFERED_FRAME) {
		/* packet was already buffered and now send due to
		 * PS poll, so do not rebuffer it */
		goto out;
	}

	if (skb_queue_len(&sta->tx_buf) >= STA_MAX_TX_BUFFER) {
		PDEBUG(DEBUG_PS, "%s: No more space in STA (%pM)'s"
		       "PS mode buffer\n",
		       local->dev->name, sta->addr);
		/* Make sure that TIM is set for the station (it might not be
		 * after AP wlan hw reset). */
		/* FIX: should fix hw reset to restore bits based on STA
		 * buffer state.. */
		hostap_set_tim(local, sta->aid, 1);
		sta->flags |= WLAN_STA_TIM;
		ret = AP_TX_DROP;
		goto out;
	}

	/* STA in PS mode, buffer frame for later delivery */
	set_tim = skb_queue_empty(&sta->tx_buf);
	skb_queue_tail(&sta->tx_buf, skb);
	/* FIX: could save RX time to skb and expire buffered frames after
	 * some time if STA does not poll for them */

	if (set_tim) {
		if (sta->flags & WLAN_STA_TIM)
			PDEBUG(DEBUG_PS2, "Re-setting TIM for aid %d\n",
			       sta->aid);
		hostap_set_tim(local, sta->aid, 1);
		sta->flags |= WLAN_STA_TIM;
	}

	ret = AP_TX_BUFFERED;

 out:
	if (sta != NULL) {
		if (ret == AP_TX_CONTINUE ||
		    ret == AP_TX_CONTINUE_NOT_AUTHORIZED) {
			sta->tx_packets++;
			sta->tx_bytes += skb->len;
			sta->last_tx = jiffies;
		}

		if ((ret == AP_TX_CONTINUE ||
		     ret == AP_TX_CONTINUE_NOT_AUTHORIZED) &&
		    sta->crypt && tx->host_encrypt) {
			tx->crypt = sta->crypt;
			tx->sta_ptr = sta; /* hostap_handle_sta_release() will
					    * be called to release sta info
					    * later */
		} else
			atomic_dec(&sta->users);
	}

	return ret;
}