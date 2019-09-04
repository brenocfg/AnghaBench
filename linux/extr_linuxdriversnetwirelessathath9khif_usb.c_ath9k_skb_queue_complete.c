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
struct sk_buff {int dummy; } ;
struct hif_device_usb {int /*<<< orphan*/  htc_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_STAT_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_STAT_INC (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ath9k_htc_txcompletion_cb (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  ln ; 
 int /*<<< orphan*/  skb_failed ; 
 int /*<<< orphan*/  skb_success ; 
 int /*<<< orphan*/  skb_success_bytes ; 

__attribute__((used)) static inline void ath9k_skb_queue_complete(struct hif_device_usb *hif_dev,
					    struct sk_buff_head *queue,
					    bool txok)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(queue)) != NULL) {
#ifdef CONFIG_ATH9K_HTC_DEBUGFS
		int ln = skb->len;
#endif
		ath9k_htc_txcompletion_cb(hif_dev->htc_handle,
					  skb, txok);
		if (txok) {
			TX_STAT_INC(skb_success);
			TX_STAT_ADD(skb_success_bytes, ln);
		}
		else
			TX_STAT_INC(skb_failed);
	}
}