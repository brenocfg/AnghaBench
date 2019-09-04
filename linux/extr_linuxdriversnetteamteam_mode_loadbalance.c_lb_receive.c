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
struct team_port {int dummy; } ;
struct team {int dummy; } ;
struct sk_buff {scalar_t__ protocol; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;
struct TYPE_2__ {unsigned char* h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_SLOW ; 
 int /*<<< orphan*/  RX_HANDLER_ANOTHER ; 
 int /*<<< orphan*/  RX_HANDLER_EXACT ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_link_local_ether_addr (unsigned char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static rx_handler_result_t lb_receive(struct team *team, struct team_port *port,
				      struct sk_buff *skb)
{
	if (unlikely(skb->protocol == htons(ETH_P_SLOW))) {
		/* LACPDU packets should go to exact delivery */
		const unsigned char *dest = eth_hdr(skb)->h_dest;

		if (is_link_local_ether_addr(dest) && dest[5] == 0x02)
			return RX_HANDLER_EXACT;
	}
	return RX_HANDLER_ANOTHER;
}