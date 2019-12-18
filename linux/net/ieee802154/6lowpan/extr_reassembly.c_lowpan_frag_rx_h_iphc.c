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
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP ; 
 int /*<<< orphan*/  RX_QUEUED ; 
 int lowpan_iphc_decompress (struct sk_buff*) ; 
 int /*<<< orphan*/  lowpan_is_iphc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static lowpan_rx_result lowpan_frag_rx_h_iphc(struct sk_buff *skb)
{
	int ret;

	if (!lowpan_is_iphc(*skb_network_header(skb)))
		return RX_CONTINUE;

	ret = lowpan_iphc_decompress(skb);
	if (ret < 0)
		return RX_DROP;

	return RX_QUEUED;
}