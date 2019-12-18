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
struct TYPE_6__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  proto; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {int label; TYPE_1__ addr; } ;
struct sw_flow_key {TYPE_3__ ip; TYPE_2__ ipv6; } ;
struct sk_buff {int dummy; } ;
struct ovs_key_ipv6 {int ipv6_tclass; int /*<<< orphan*/  ipv6_hlimit; scalar_t__ ipv6_label; int /*<<< orphan*/  ipv6_dst; int /*<<< orphan*/  ipv6_src; } ;
struct ipv6hdr {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  masked ;
typedef  int __be32 ;

/* Variables and functions */
 int IP6_FH_F_SKIP_RH ; 
 int /*<<< orphan*/  IPV6_FLOWINFO_FLOWLABEL ; 
 scalar_t__ NEXTHDR_ROUTING ; 
 int /*<<< orphan*/  OVS_SET_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_change_dsfield (struct ipv6hdr*,int,int) ; 
 scalar_t__ ipv6_ext_hdr (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_find_hdr (struct sk_buff*,unsigned int*,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ is_ipv6_mask_nonzero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_ipv6_addr (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  set_ipv6_addr (struct sk_buff*,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  set_ipv6_fl (struct ipv6hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_ensure_writable (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_ipv6(struct sk_buff *skb, struct sw_flow_key *flow_key,
		    const struct ovs_key_ipv6 *key,
		    const struct ovs_key_ipv6 *mask)
{
	struct ipv6hdr *nh;
	int err;

	err = skb_ensure_writable(skb, skb_network_offset(skb) +
				  sizeof(struct ipv6hdr));
	if (unlikely(err))
		return err;

	nh = ipv6_hdr(skb);

	/* Setting an IP addresses is typically only a side effect of
	 * matching on them in the current userspace implementation, so it
	 * makes sense to check if the value actually changed.
	 */
	if (is_ipv6_mask_nonzero(mask->ipv6_src)) {
		__be32 *saddr = (__be32 *)&nh->saddr;
		__be32 masked[4];

		mask_ipv6_addr(saddr, key->ipv6_src, mask->ipv6_src, masked);

		if (unlikely(memcmp(saddr, masked, sizeof(masked)))) {
			set_ipv6_addr(skb, flow_key->ip.proto, saddr, masked,
				      true);
			memcpy(&flow_key->ipv6.addr.src, masked,
			       sizeof(flow_key->ipv6.addr.src));
		}
	}
	if (is_ipv6_mask_nonzero(mask->ipv6_dst)) {
		unsigned int offset = 0;
		int flags = IP6_FH_F_SKIP_RH;
		bool recalc_csum = true;
		__be32 *daddr = (__be32 *)&nh->daddr;
		__be32 masked[4];

		mask_ipv6_addr(daddr, key->ipv6_dst, mask->ipv6_dst, masked);

		if (unlikely(memcmp(daddr, masked, sizeof(masked)))) {
			if (ipv6_ext_hdr(nh->nexthdr))
				recalc_csum = (ipv6_find_hdr(skb, &offset,
							     NEXTHDR_ROUTING,
							     NULL, &flags)
					       != NEXTHDR_ROUTING);

			set_ipv6_addr(skb, flow_key->ip.proto, daddr, masked,
				      recalc_csum);
			memcpy(&flow_key->ipv6.addr.dst, masked,
			       sizeof(flow_key->ipv6.addr.dst));
		}
	}
	if (mask->ipv6_tclass) {
		ipv6_change_dsfield(nh, ~mask->ipv6_tclass, key->ipv6_tclass);
		flow_key->ip.tos = ipv6_get_dsfield(nh);
	}
	if (mask->ipv6_label) {
		set_ipv6_fl(nh, ntohl(key->ipv6_label),
			    ntohl(mask->ipv6_label));
		flow_key->ipv6.label =
		    *(__be32 *)nh & htonl(IPV6_FLOWINFO_FLOWLABEL);
	}
	if (mask->ipv6_hlimit) {
		OVS_SET_MASKED(nh->hop_limit, key->ipv6_hlimit,
			       mask->ipv6_hlimit);
		flow_key->ip.ttl = nh->hop_limit;
	}
	return 0;
}