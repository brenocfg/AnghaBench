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
struct sk_buff_head {int dummy; } ;
struct ieee80211_rx_data {int dummy; } ;
typedef  scalar_t__ ieee80211_rx_result ;

/* Variables and functions */
 scalar_t__ RX_CONTINUE ; 
 scalar_t__ RX_DROP_MONITOR ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 scalar_t__ ieee80211_rx_h_check (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_rx_h_check_dup (struct ieee80211_rx_data*) ; 
 int /*<<< orphan*/  ieee80211_rx_handlers (struct ieee80211_rx_data*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_rx_handlers_result (struct ieee80211_rx_data*,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_rx_reorder_ampdu (struct ieee80211_rx_data*,struct sk_buff_head*) ; 

__attribute__((used)) static void ieee80211_invoke_rx_handlers(struct ieee80211_rx_data *rx)
{
	struct sk_buff_head reorder_release;
	ieee80211_rx_result res = RX_DROP_MONITOR;

	__skb_queue_head_init(&reorder_release);

#define CALL_RXH(rxh)			\
	do {				\
		res = rxh(rx);		\
		if (res != RX_CONTINUE)	\
			goto rxh_next;  \
	} while (0)

	CALL_RXH(ieee80211_rx_h_check_dup);
	CALL_RXH(ieee80211_rx_h_check);

	ieee80211_rx_reorder_ampdu(rx, &reorder_release);

	ieee80211_rx_handlers(rx, &reorder_release);
	return;

 rxh_next:
	ieee80211_rx_handlers_result(rx, res);

#undef CALL_RXH
}