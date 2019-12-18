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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  lowpan_rx_result ;

/* Variables and functions */
 int LOWPAN_DISPATCH_FRAG_MASK ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP ; 
 int /*<<< orphan*/  RX_QUEUED ; 
 int lowpan_frag_rcv (struct sk_buff*,int) ; 
 scalar_t__ lowpan_is_frag1 (int) ; 
 scalar_t__ lowpan_is_fragn (int) ; 
 int* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static lowpan_rx_result lowpan_rx_h_frag(struct sk_buff *skb)
{
	int ret;

	if (!(lowpan_is_frag1(*skb_network_header(skb)) ||
	      lowpan_is_fragn(*skb_network_header(skb))))
		return RX_CONTINUE;

	ret = lowpan_frag_rcv(skb, *skb_network_header(skb) &
			      LOWPAN_DISPATCH_FRAG_MASK);
	if (ret == 1)
		return RX_QUEUED;

	/* Packet is freed by lowpan_frag_rcv on error or put into the frag
	 * bucket.
	 */
	return RX_DROP;
}