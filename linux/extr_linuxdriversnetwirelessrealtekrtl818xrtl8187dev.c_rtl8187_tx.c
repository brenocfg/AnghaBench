#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct urb {int /*<<< orphan*/  transfer_flags; struct rtl8187_priv* priv; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct rtl8187b_tx_hdr {int /*<<< orphan*/  tx_duration; void* retry; void* rts_duration; void* flags; } ;
struct rtl8187_tx_hdr {void* retry; void* rts_duration; scalar_t__ len; void* flags; } ;
struct rtl8187_priv {int seqno; int /*<<< orphan*/  anchored; int /*<<< orphan*/  udev; int /*<<< orphan*/  vif; int /*<<< orphan*/  is_rtl8187b; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; struct urb** rate_driver_data; int /*<<< orphan*/  band; TYPE_2__ control; } ;
struct ieee80211_tx_control {int dummy; } ;
struct ieee80211_rate {int hw_value; } ;
struct ieee80211_hw {int /*<<< orphan*/  transfer_flags; struct rtl8187_priv* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  seq_ctrl; } ;
typedef  void* __le16 ;
struct TYPE_6__ {int hw_value; } ;
struct TYPE_4__ {int flags; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_SCTL_FRAG ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int IEEE80211_TX_CTL_FIRST_FRAGMENT ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int RTL818X_TX_DESC_FLAG_CTS ; 
 int RTL818X_TX_DESC_FLAG_MOREFRAG ; 
 int RTL818X_TX_DESC_FLAG_NO_ENC ; 
 int RTL818X_TX_DESC_FLAG_RTS ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 void* ieee80211_ctstoself_duration (struct urb*,int /*<<< orphan*/ ,int,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_generic_frame_duration (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ieee80211_rate*) ; 
 TYPE_3__* ieee80211_get_rts_cts_rate (struct urb*,struct ieee80211_tx_info*) ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (struct urb*,struct ieee80211_tx_info*) ; 
 scalar_t__ ieee80211_has_morefrags (int /*<<< orphan*/ ) ; 
 void* ieee80211_rts_duration (struct urb*,int /*<<< orphan*/ ,int,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rtl8187b_tx_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8187_tx_cb ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 void* skb_push (struct sk_buff*,int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,unsigned int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void rtl8187_tx(struct ieee80211_hw *dev,
		       struct ieee80211_tx_control *control,
		       struct sk_buff *skb)
{
	struct rtl8187_priv *priv = dev->priv;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *tx_hdr =	(struct ieee80211_hdr *)(skb->data);
	unsigned int ep;
	void *buf;
	struct urb *urb;
	__le16 rts_dur = 0;
	u32 flags;
	int rc;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		kfree_skb(skb);
		return;
	}

	flags = skb->len;
	flags |= RTL818X_TX_DESC_FLAG_NO_ENC;

	flags |= ieee80211_get_tx_rate(dev, info)->hw_value << 24;
	if (ieee80211_has_morefrags(tx_hdr->frame_control))
		flags |= RTL818X_TX_DESC_FLAG_MOREFRAG;

	/* HW will perform RTS-CTS when only RTS flags is set.
	 * HW will perform CTS-to-self when both RTS and CTS flags are set.
	 * RTS rate and RTS duration will be used also for CTS-to-self.
	 */
	if (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) {
		flags |= RTL818X_TX_DESC_FLAG_RTS;
		flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_dur = ieee80211_rts_duration(dev, priv->vif,
						 skb->len, info);
	} else if (info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT) {
		flags |= RTL818X_TX_DESC_FLAG_RTS | RTL818X_TX_DESC_FLAG_CTS;
		flags |= ieee80211_get_rts_cts_rate(dev, info)->hw_value << 19;
		rts_dur = ieee80211_ctstoself_duration(dev, priv->vif,
						 skb->len, info);
	}

	if (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) {
		if (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
			priv->seqno += 0x10;
		tx_hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		tx_hdr->seq_ctrl |= cpu_to_le16(priv->seqno);
	}

	if (!priv->is_rtl8187b) {
		struct rtl8187_tx_hdr *hdr = skb_push(skb, sizeof(*hdr));
		hdr->flags = cpu_to_le32(flags);
		hdr->len = 0;
		hdr->rts_duration = rts_dur;
		hdr->retry = cpu_to_le32((info->control.rates[0].count - 1) << 8);
		buf = hdr;

		ep = 2;
	} else {
		/* fc needs to be calculated before skb_push() */
		unsigned int epmap[4] = { 6, 7, 5, 4 };
		u16 fc = le16_to_cpu(tx_hdr->frame_control);

		struct rtl8187b_tx_hdr *hdr = skb_push(skb, sizeof(*hdr));
		struct ieee80211_rate *txrate =
			ieee80211_get_tx_rate(dev, info);
		memset(hdr, 0, sizeof(*hdr));
		hdr->flags = cpu_to_le32(flags);
		hdr->rts_duration = rts_dur;
		hdr->retry = cpu_to_le32((info->control.rates[0].count - 1) << 8);
		hdr->tx_duration =
			ieee80211_generic_frame_duration(dev, priv->vif,
							 info->band,
							 skb->len, txrate);
		buf = hdr;

		if ((fc & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_MGMT)
			ep = 12;
		else
			ep = epmap[skb_get_queue_mapping(skb)];
	}

	info->rate_driver_data[0] = dev;
	info->rate_driver_data[1] = urb;

	usb_fill_bulk_urb(urb, priv->udev, usb_sndbulkpipe(priv->udev, ep),
			  buf, skb->len, rtl8187_tx_cb, skb);
	urb->transfer_flags |= URB_ZERO_PACKET;
	usb_anchor_urb(urb, &priv->anchored);
	rc = usb_submit_urb(urb, GFP_ATOMIC);
	if (rc < 0) {
		usb_unanchor_urb(urb);
		kfree_skb(skb);
	}
	usb_free_urb(urb);
}