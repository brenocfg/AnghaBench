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
struct xfrm_state {int dummy; } ;
struct sk_buff {int data; scalar_t__ transport_header; scalar_t__ network_header; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (scalar_t__) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int xfrm4_transport_input(struct xfrm_state *x, struct sk_buff *skb)
{
	int ihl = skb->data - skb_transport_header(skb);

	if (skb->transport_header != skb->network_header) {
		memmove(skb_transport_header(skb),
			skb_network_header(skb), ihl);
		skb->network_header = skb->transport_header;
	}
	ip_hdr(skb)->tot_len = htons(skb->len + ihl);
	skb_reset_transport_header(skb);
	return 0;
}