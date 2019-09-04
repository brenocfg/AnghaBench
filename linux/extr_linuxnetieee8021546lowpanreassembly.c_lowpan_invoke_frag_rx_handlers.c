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
typedef  scalar_t__ lowpan_rx_result ;

/* Variables and functions */
 scalar_t__ RX_CONTINUE ; 
 scalar_t__ lowpan_frag_rx_h_iphc (struct sk_buff*) ; 
 int lowpan_frag_rx_handlers_result (struct sk_buff*,scalar_t__) ; 
 scalar_t__ lowpan_rx_h_ipv6 (struct sk_buff*) ; 

__attribute__((used)) static int lowpan_invoke_frag_rx_handlers(struct sk_buff *skb)
{
	lowpan_rx_result res;

#define CALL_RXH(rxh)			\
	do {				\
		res = rxh(skb);	\
		if (res != RX_CONTINUE)	\
			goto rxh_next;	\
	} while (0)

	/* likely at first */
	CALL_RXH(lowpan_frag_rx_h_iphc);
	CALL_RXH(lowpan_rx_h_ipv6);

rxh_next:
	return lowpan_frag_rx_handlers_result(skb, res);
#undef CALL_RXH
}