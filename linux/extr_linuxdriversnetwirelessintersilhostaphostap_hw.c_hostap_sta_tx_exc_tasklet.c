#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; scalar_t__ data; } ;
struct hfa384x_tx_frame {int /*<<< orphan*/  frame_control; } ;
struct TYPE_3__ {int /*<<< orphan*/  sta_tx_exc_list; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int hostap_80211_get_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_handle_sta_tx_exc (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void hostap_sta_tx_exc_tasklet(unsigned long data)
{
	local_info_t *local = (local_info_t *) data;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&local->sta_tx_exc_list)) != NULL) {
		struct hfa384x_tx_frame *txdesc =
			(struct hfa384x_tx_frame *) skb->data;

		if (skb->len >= sizeof(*txdesc)) {
			/* Convert Prism2 RX structure into IEEE 802.11 header
			 */
			int hdrlen = hostap_80211_get_hdrlen(txdesc->frame_control);
			memmove(skb_pull(skb, sizeof(*txdesc) - hdrlen),
				&txdesc->frame_control, hdrlen);

			hostap_handle_sta_tx_exc(local, skb);
		}
		dev_kfree_skb(skb);
	}
}