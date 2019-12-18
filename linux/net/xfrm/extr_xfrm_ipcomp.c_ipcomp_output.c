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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  spi; } ;
struct xfrm_state {TYPE_1__ id; struct ipcomp_data* data; } ;
struct sk_buff {scalar_t__ len; } ;
struct ipcomp_data {scalar_t__ threshold; } ;
struct ip_comp_hdr {int /*<<< orphan*/  cpi; scalar_t__ flags; int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_COMP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ip_comp_hdr* ip_comp_hdr (struct sk_buff*) ; 
 int ipcomp_compress (struct xfrm_state*,struct sk_buff*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_linearize_cow (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

int ipcomp_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	struct ip_comp_hdr *ipch;
	struct ipcomp_data *ipcd = x->data;

	if (skb->len < ipcd->threshold) {
		/* Don't bother compressing */
		goto out_ok;
	}

	if (skb_linearize_cow(skb))
		goto out_ok;

	err = ipcomp_compress(x, skb);

	if (err) {
		goto out_ok;
	}

	/* Install ipcomp header, convert into ipcomp datagram. */
	ipch = ip_comp_hdr(skb);
	ipch->nexthdr = *skb_mac_header(skb);
	ipch->flags = 0;
	ipch->cpi = htons((u16 )ntohl(x->id.spi));
	*skb_mac_header(skb) = IPPROTO_COMP;
out_ok:
	skb_push(skb, -skb_network_offset(skb));
	return 0;
}