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
struct TYPE_2__ {scalar_t__ header_len; } ;
struct xfrm_state {TYPE_1__ props; } ;
struct xfrm_offload {int flags; } ;
struct sk_buff {scalar_t__ mac_len; scalar_t__ network_header; scalar_t__ transport_header; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int XFRM_GSO_SEGMENT ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static void xfrm4_mode_tunnel_xmit(struct xfrm_state *x, struct sk_buff *skb)
{
	struct xfrm_offload *xo = xfrm_offload(skb);

	if (xo->flags & XFRM_GSO_SEGMENT)
		skb->transport_header = skb->network_header +
					sizeof(struct iphdr);

	skb_reset_mac_len(skb);
	pskb_pull(skb, skb->mac_len + x->props.header_len);
}