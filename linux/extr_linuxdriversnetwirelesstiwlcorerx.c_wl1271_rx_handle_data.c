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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct wl1271_rx_descriptor {scalar_t__ packet_class; int status; int hlid; scalar_t__ pad_len; } ;
struct wl1271 {int /*<<< orphan*/  netstack_work; int /*<<< orphan*/  freezable_wq; int /*<<< orphan*/  deferred_rx_queue; int /*<<< orphan*/  plt; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  frame_control; } ;
typedef  enum wl_rx_buf_align { ____Placeholder_wl_rx_buf_align } wl_rx_buf_align ;

/* Variables and functions */
 int DEBUG_CMD ; 
 int DEBUG_RX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_SCTL_SEQ ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int RX_BUF_ALIGN ; 
 int WL1271_RX_DESC_DECRYPT_FAIL ; 
 int WL1271_RX_DESC_STATUS_MASK ; 
 scalar_t__ WL12XX_RX_CLASS_LOGGER ; 
 int WLCORE_RX_BUF_PADDED ; 
 int WLCORE_RX_BUF_UNALIGNED ; 
 struct sk_buff* __dev_alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int,char*,struct sk_buff*,scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  wl1271_dump (int,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int /*<<< orphan*/  wl1271_rx_status (struct wl1271*,struct wl1271_rx_descriptor*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int,int) ; 
 int /*<<< orphan*/  wl12xx_copy_fwlog (struct wl1271*,int*,size_t) ; 
 int wlcore_hw_get_rx_packet_len (struct wl1271*,int*,int) ; 
 int /*<<< orphan*/  wlcore_hw_set_rx_csum (struct wl1271*,struct wl1271_rx_descriptor*,struct sk_buff*) ; 

__attribute__((used)) static int wl1271_rx_handle_data(struct wl1271 *wl, u8 *data, u32 length,
				 enum wl_rx_buf_align rx_align, u8 *hlid)
{
	struct wl1271_rx_descriptor *desc;
	struct sk_buff *skb;
	struct ieee80211_hdr *hdr;
	u8 beacon = 0;
	u8 is_data = 0;
	u8 reserved = 0, offset_to_data = 0;
	u16 seq_num;
	u32 pkt_data_len;

	/*
	 * In PLT mode we seem to get frames and mac80211 warns about them,
	 * workaround this by not retrieving them at all.
	 */
	if (unlikely(wl->plt))
		return -EINVAL;

	pkt_data_len = wlcore_hw_get_rx_packet_len(wl, data, length);
	if (!pkt_data_len) {
		wl1271_error("Invalid packet arrived from HW. length %d",
			     length);
		return -EINVAL;
	}

	if (rx_align == WLCORE_RX_BUF_UNALIGNED)
		reserved = RX_BUF_ALIGN;
	else if (rx_align == WLCORE_RX_BUF_PADDED)
		offset_to_data = RX_BUF_ALIGN;

	/* the data read starts with the descriptor */
	desc = (struct wl1271_rx_descriptor *) data;

	if (desc->packet_class == WL12XX_RX_CLASS_LOGGER) {
		size_t len = length - sizeof(*desc);
		wl12xx_copy_fwlog(wl, data + sizeof(*desc), len);
		return 0;
	}

	/* discard corrupted packets */
	if (desc->status & WL1271_RX_DESC_DECRYPT_FAIL) {
		hdr = (void *)(data + sizeof(*desc) + offset_to_data);
		wl1271_warning("corrupted packet in RX: status: 0x%x len: %d",
			       desc->status & WL1271_RX_DESC_STATUS_MASK,
			       pkt_data_len);
		wl1271_dump((DEBUG_RX|DEBUG_CMD), "PKT: ", data + sizeof(*desc),
			    min(pkt_data_len,
				ieee80211_hdrlen(hdr->frame_control)));
		return -EINVAL;
	}

	/* skb length not including rx descriptor */
	skb = __dev_alloc_skb(pkt_data_len + reserved, GFP_KERNEL);
	if (!skb) {
		wl1271_error("Couldn't allocate RX frame");
		return -ENOMEM;
	}

	/* reserve the unaligned payload(if any) */
	skb_reserve(skb, reserved);

	/*
	 * Copy packets from aggregation buffer to the skbs without rx
	 * descriptor and with packet payload aligned care. In case of unaligned
	 * packets copy the packets in offset of 2 bytes guarantee IP header
	 * payload aligned to 4 bytes.
	 */
	skb_put_data(skb, data + sizeof(*desc), pkt_data_len);
	if (rx_align == WLCORE_RX_BUF_PADDED)
		skb_pull(skb, RX_BUF_ALIGN);

	*hlid = desc->hlid;

	hdr = (struct ieee80211_hdr *)skb->data;
	if (ieee80211_is_beacon(hdr->frame_control))
		beacon = 1;
	if (ieee80211_is_data_present(hdr->frame_control))
		is_data = 1;

	wl1271_rx_status(wl, desc, IEEE80211_SKB_RXCB(skb), beacon,
			 ieee80211_is_probe_resp(hdr->frame_control));
	wlcore_hw_set_rx_csum(wl, desc, skb);

	seq_num = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	wl1271_debug(DEBUG_RX, "rx skb 0x%p: %d B %s seq %d hlid %d", skb,
		     skb->len - desc->pad_len,
		     beacon ? "beacon" : "",
		     seq_num, *hlid);

	skb_queue_tail(&wl->deferred_rx_queue, skb);
	queue_work(wl->freezable_wq, &wl->netstack_work);

	return is_data;
}