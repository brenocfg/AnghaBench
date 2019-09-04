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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {int info0; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct htt_rx_desc {TYPE_2__ msdu_end; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  RX_MSDU_END_INFO0_LAST_MSDU ; 
 scalar_t__ WARN_ON (int) ; 
 int __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct sk_buff* skb_peek_tail (struct sk_buff_head*) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static int ath10k_htt_rx_extract_amsdu(struct sk_buff_head *list,
				       struct sk_buff_head *amsdu)
{
	struct sk_buff *msdu;
	struct htt_rx_desc *rxd;

	if (skb_queue_empty(list))
		return -ENOBUFS;

	if (WARN_ON(!skb_queue_empty(amsdu)))
		return -EINVAL;

	while ((msdu = __skb_dequeue(list))) {
		__skb_queue_tail(amsdu, msdu);

		rxd = (void *)msdu->data - sizeof(*rxd);
		if (rxd->msdu_end.common.info0 &
		    __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU))
			break;
	}

	msdu = skb_peek_tail(amsdu);
	rxd = (void *)msdu->data - sizeof(*rxd);
	if (!(rxd->msdu_end.common.info0 &
	      __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU))) {
		skb_queue_splice_init(amsdu, list);
		return -EAGAIN;
	}

	return 0;
}