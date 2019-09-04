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
struct sta_info {int flags; int /*<<< orphan*/  tx_buf; } ;
struct sk_buff {scalar_t__ cb; } ;
struct hostap_skb_tx_data {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAP_TX_FLAGS_ADD_MOREDATA ; 
 int /*<<< orphan*/  HOSTAP_TX_FLAGS_BUFFERED_FRAME ; 
 int WLAN_STA_PS ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pspoll_send_buffered(local_info_t *local, struct sta_info *sta,
				 struct sk_buff *skb)
{
	struct hostap_skb_tx_data *meta;

	if (!(sta->flags & WLAN_STA_PS)) {
		/* Station has moved to non-PS mode, so send all buffered
		 * frames using normal device queue. */
		dev_queue_xmit(skb);
		return;
	}

	/* add a flag for hostap_handle_sta_tx() to know that this skb should
	 * be passed through even though STA is using PS */
	meta = (struct hostap_skb_tx_data *) skb->cb;
	meta->flags |= HOSTAP_TX_FLAGS_BUFFERED_FRAME;
	if (!skb_queue_empty(&sta->tx_buf)) {
		/* indicate to STA that more frames follow */
		meta->flags |= HOSTAP_TX_FLAGS_ADD_MOREDATA;
	}
	dev_queue_xmit(skb);
}