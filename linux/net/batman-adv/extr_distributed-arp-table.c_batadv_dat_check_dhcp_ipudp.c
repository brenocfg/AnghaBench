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
struct udphdr {int version; int ihl; scalar_t__ protocol; scalar_t__ source; int /*<<< orphan*/  saddr; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int version; int ihl; scalar_t__ protocol; scalar_t__ source; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  _udphdr ;
typedef  int /*<<< orphan*/  _iphdr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int) ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct udphdr*) ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool
batadv_dat_check_dhcp_ipudp(struct sk_buff *skb, __be32 *ip_src)
{
	unsigned int offset = skb_network_offset(skb);
	struct udphdr *udphdr, _udphdr;
	struct iphdr *iphdr, _iphdr;

	iphdr = skb_header_pointer(skb, offset, sizeof(_iphdr), &_iphdr);
	if (!iphdr || iphdr->version != 4 || iphdr->ihl * 4 < sizeof(_iphdr))
		return false;

	if (iphdr->protocol != IPPROTO_UDP)
		return false;

	offset += iphdr->ihl * 4;
	skb_set_transport_header(skb, offset);

	udphdr = skb_header_pointer(skb, offset, sizeof(_udphdr), &_udphdr);
	if (!udphdr || udphdr->source != htons(67))
		return false;

	*ip_src = get_unaligned(&iphdr->saddr);

	return true;
}