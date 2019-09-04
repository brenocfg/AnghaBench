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
typedef  int /*<<< orphan*/  u16 ;
struct wl1251 {int /*<<< orphan*/  hw; } ;
struct tx_double_buffer_desc {int id; int /*<<< orphan*/  xmit_queue; int /*<<< orphan*/  expiry_time; void* rate; void* length; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_rate {scalar_t__ hw_value; } ;

/* Variables and functions */
 int EINVAL ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 struct tx_double_buffer_desc* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wl1251_tx_control (struct tx_double_buffer_desc*,struct ieee80211_tx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_tx_frag_block_num (struct tx_double_buffer_desc*) ; 
 int /*<<< orphan*/  wl1251_tx_get_queue (int /*<<< orphan*/ ) ; 
 int wl1251_tx_id (struct wl1251*,struct sk_buff*) ; 

__attribute__((used)) static int wl1251_tx_fill_hdr(struct wl1251 *wl, struct sk_buff *skb,
			      struct ieee80211_tx_info *control)
{
	struct tx_double_buffer_desc *tx_hdr;
	struct ieee80211_rate *rate;
	int id;
	u16 fc;

	if (!skb)
		return -EINVAL;

	id = wl1251_tx_id(wl, skb);
	if (id < 0)
		return id;

	fc = *(u16 *)skb->data;
	tx_hdr = skb_push(skb, sizeof(*tx_hdr));

	tx_hdr->length = cpu_to_le16(skb->len - sizeof(*tx_hdr));
	rate = ieee80211_get_tx_rate(wl->hw, control);
	tx_hdr->rate = cpu_to_le16(rate->hw_value);
	tx_hdr->expiry_time = cpu_to_le32(1 << 16);
	tx_hdr->id = id;

	tx_hdr->xmit_queue = wl1251_tx_get_queue(skb_get_queue_mapping(skb));

	wl1251_tx_control(tx_hdr, control, fc);
	wl1251_tx_frag_block_num(tx_hdr);

	return 0;
}