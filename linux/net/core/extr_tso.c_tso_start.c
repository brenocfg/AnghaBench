#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tso_t {size_t next_frag_idx; int ipv6; scalar_t__ size; scalar_t__ data; int /*<<< orphan*/  tcp_seq; int /*<<< orphan*/  ip_id; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {size_t nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_address (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

void tso_start(struct sk_buff *skb, struct tso_t *tso)
{
	int hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

	tso->ip_id = ntohs(ip_hdr(skb)->id);
	tso->tcp_seq = ntohl(tcp_hdr(skb)->seq);
	tso->next_frag_idx = 0;
	tso->ipv6 = vlan_get_protocol(skb) == htons(ETH_P_IPV6);

	/* Build first data */
	tso->size = skb_headlen(skb) - hdr_len;
	tso->data = skb->data + hdr_len;
	if ((tso->size == 0) &&
	    (tso->next_frag_idx < skb_shinfo(skb)->nr_frags)) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[tso->next_frag_idx];

		/* Move to next segment */
		tso->size = skb_frag_size(frag);
		tso->data = skb_frag_address(frag);
		tso->next_frag_idx++;
	}
}