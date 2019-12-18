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
struct tso_t {int ip_id; int /*<<< orphan*/  tcp_seq; int /*<<< orphan*/  ipv6; } ;
struct tcphdr {scalar_t__ rst; scalar_t__ fin; scalar_t__ psh; int /*<<< orphan*/  seq; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ipv6hdr {void* payload_len; } ;
struct iphdr {void* tot_len; void* id; } ;

/* Variables and functions */
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 

void tso_build_hdr(struct sk_buff *skb, char *hdr, struct tso_t *tso,
		   int size, bool is_last)
{
	struct tcphdr *tcph;
	int hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	int mac_hdr_len = skb_network_offset(skb);

	memcpy(hdr, skb->data, hdr_len);
	if (!tso->ipv6) {
		struct iphdr *iph = (void *)(hdr + mac_hdr_len);

		iph->id = htons(tso->ip_id);
		iph->tot_len = htons(size + hdr_len - mac_hdr_len);
		tso->ip_id++;
	} else {
		struct ipv6hdr *iph = (void *)(hdr + mac_hdr_len);

		iph->payload_len = htons(size + tcp_hdrlen(skb));
	}
	tcph = (struct tcphdr *)(hdr + skb_transport_offset(skb));
	put_unaligned_be32(tso->tcp_seq, &tcph->seq);

	if (!is_last) {
		/* Clear all special flags for not last packet */
		tcph->psh = 0;
		tcph->fin = 0;
		tcph->rst = 0;
	}
}