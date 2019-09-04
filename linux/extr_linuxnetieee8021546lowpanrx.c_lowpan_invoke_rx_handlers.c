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
 scalar_t__ lowpan_rx_h_bc0 (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_dff (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_esc (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_frag (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_hc1 (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_iphc (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_ipv6 (struct sk_buff*) ; 
 scalar_t__ lowpan_rx_h_mesh (struct sk_buff*) ; 
 int lowpan_rx_handlers_result (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int lowpan_invoke_rx_handlers(struct sk_buff *skb)
{
	lowpan_rx_result res;

#define CALL_RXH(rxh)			\
	do {				\
		res = rxh(skb);	\
		if (res != RX_CONTINUE)	\
			goto rxh_next;	\
	} while (0)

	/* likely at first */
	CALL_RXH(lowpan_rx_h_iphc);
	CALL_RXH(lowpan_rx_h_frag);
	CALL_RXH(lowpan_rx_h_ipv6);
	CALL_RXH(lowpan_rx_h_esc);
	CALL_RXH(lowpan_rx_h_hc1);
	CALL_RXH(lowpan_rx_h_dff);
	CALL_RXH(lowpan_rx_h_bc0);
	CALL_RXH(lowpan_rx_h_mesh);

rxh_next:
	return lowpan_rx_handlers_result(skb, res);
#undef CALL_RXH
}