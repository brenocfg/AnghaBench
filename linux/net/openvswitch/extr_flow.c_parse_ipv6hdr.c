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
struct TYPE_6__ {int proto; int /*<<< orphan*/  frag; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {int label; TYPE_1__ addr; } ;
struct sw_flow_key {TYPE_3__ ip; TYPE_2__ ipv6; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  hop_limit; } ;
typedef  int __be32 ;

/* Variables and functions */
 int EPROTO ; 
 int IP6_FH_F_FRAG ; 
 int /*<<< orphan*/  IPV6_FLOWINFO_FLOWLABEL ; 
 int NEXTHDR_NONE ; 
 int /*<<< orphan*/  OVS_FRAG_TYPE_FIRST ; 
 int /*<<< orphan*/  OVS_FRAG_TYPE_LATER ; 
 int /*<<< orphan*/  OVS_FRAG_TYPE_NONE ; 
 int check_header (struct sk_buff*,unsigned int) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int ipv6_find_hdr (struct sk_buff*,unsigned int*,int,unsigned short*,int*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_ipv6hdr(struct sk_buff *skb, struct sw_flow_key *key)
{
	unsigned short frag_off;
	unsigned int payload_ofs = 0;
	unsigned int nh_ofs = skb_network_offset(skb);
	unsigned int nh_len;
	struct ipv6hdr *nh;
	int err, nexthdr, flags = 0;

	err = check_header(skb, nh_ofs + sizeof(*nh));
	if (unlikely(err))
		return err;

	nh = ipv6_hdr(skb);

	key->ip.proto = NEXTHDR_NONE;
	key->ip.tos = ipv6_get_dsfield(nh);
	key->ip.ttl = nh->hop_limit;
	key->ipv6.label = *(__be32 *)nh & htonl(IPV6_FLOWINFO_FLOWLABEL);
	key->ipv6.addr.src = nh->saddr;
	key->ipv6.addr.dst = nh->daddr;

	nexthdr = ipv6_find_hdr(skb, &payload_ofs, -1, &frag_off, &flags);
	if (flags & IP6_FH_F_FRAG) {
		if (frag_off) {
			key->ip.frag = OVS_FRAG_TYPE_LATER;
			key->ip.proto = nexthdr;
			return 0;
		}
		key->ip.frag = OVS_FRAG_TYPE_FIRST;
	} else {
		key->ip.frag = OVS_FRAG_TYPE_NONE;
	}

	/* Delayed handling of error in ipv6_find_hdr() as it
	 * always sets flags and frag_off to a valid value which may be
	 * used to set key->ip.frag above.
	 */
	if (unlikely(nexthdr < 0))
		return -EPROTO;

	nh_len = payload_ofs - nh_ofs;
	skb_set_transport_header(skb, nh_ofs + nh_len);
	key->ip.proto = nexthdr;
	return nh_len;
}