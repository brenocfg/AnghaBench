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
struct socket {scalar_t__ type; } ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ALL ; 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ dev_parse_header_protocol (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_probe_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void packet_parse_headers(struct sk_buff *skb, struct socket *sock)
{
	if ((!skb->protocol || skb->protocol == htons(ETH_P_ALL)) &&
	    sock->type == SOCK_RAW) {
		skb_reset_mac_header(skb);
		skb->protocol = dev_parse_header_protocol(skb);
	}

	skb_probe_transport_header(skb);
}