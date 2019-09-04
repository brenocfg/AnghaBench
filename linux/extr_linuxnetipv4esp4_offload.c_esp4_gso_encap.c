#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  spi; } ;
struct xfrm_state {TYPE_1__ id; } ;
struct xfrm_offload {int proto; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int protocol; } ;
struct ip_esp_hdr {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct TYPE_6__ {int /*<<< orphan*/  low; } ;
struct TYPE_7__ {TYPE_2__ output; } ;
struct TYPE_8__ {TYPE_3__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ESP ; 
 TYPE_4__* XFRM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct ip_esp_hdr* ip_esp_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static void esp4_gso_encap(struct xfrm_state *x, struct sk_buff *skb)
{
	struct ip_esp_hdr *esph;
	struct iphdr *iph = ip_hdr(skb);
	struct xfrm_offload *xo = xfrm_offload(skb);
	int proto = iph->protocol;

	skb_push(skb, -skb_network_offset(skb));
	esph = ip_esp_hdr(skb);
	*skb_mac_header(skb) = IPPROTO_ESP;

	esph->spi = x->id.spi;
	esph->seq_no = htonl(XFRM_SKB_CB(skb)->seq.output.low);

	xo->proto = proto;
}