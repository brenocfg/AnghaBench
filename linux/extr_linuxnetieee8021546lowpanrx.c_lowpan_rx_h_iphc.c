#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  lowpan_rx_result ;
struct TYPE_2__ {scalar_t__ d_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int /*<<< orphan*/  RX_QUEUED ; 
 TYPE_1__* lowpan_802154_cb (struct sk_buff*) ; 
 int lowpan_iphc_decompress (struct sk_buff*) ; 
 int /*<<< orphan*/  lowpan_is_iphc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static lowpan_rx_result lowpan_rx_h_iphc(struct sk_buff *skb)
{
	int ret;

	if (!lowpan_is_iphc(*skb_network_header(skb)))
		return RX_CONTINUE;

	/* Setting datagram_offset to zero indicates non frag handling
	 * while doing lowpan_header_decompress.
	 */
	lowpan_802154_cb(skb)->d_size = 0;

	ret = lowpan_iphc_decompress(skb);
	if (ret < 0)
		return RX_DROP_UNUSABLE;

	return RX_QUEUED;
}