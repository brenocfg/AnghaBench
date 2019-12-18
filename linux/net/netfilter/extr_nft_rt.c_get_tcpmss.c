#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct tcphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_8__ {TYPE_2__ ip6; TYPE_1__ ip4; } ;
struct flowi {TYPE_3__ u; } ;
typedef  struct dst_entry const dst_entry ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_10__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int TCP_MSS_DEFAULT ; 
 int dst_mtu (struct dst_entry const*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry const*) ; 
 TYPE_5__* ip_hdr (struct sk_buff const*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  nf_route (int /*<<< orphan*/ ,struct dst_entry const**,struct flowi*,int,int) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int nft_pf (struct nft_pktinfo const*) ; 

__attribute__((used)) static u16 get_tcpmss(const struct nft_pktinfo *pkt, const struct dst_entry *skbdst)
{
	u32 minlen = sizeof(struct ipv6hdr), mtu = dst_mtu(skbdst);
	const struct sk_buff *skb = pkt->skb;
	struct dst_entry *dst = NULL;
	struct flowi fl;

	memset(&fl, 0, sizeof(fl));

	switch (nft_pf(pkt)) {
	case NFPROTO_IPV4:
		fl.u.ip4.daddr = ip_hdr(skb)->saddr;
		minlen = sizeof(struct iphdr) + sizeof(struct tcphdr);
		break;
	case NFPROTO_IPV6:
		fl.u.ip6.daddr = ipv6_hdr(skb)->saddr;
		minlen = sizeof(struct ipv6hdr) + sizeof(struct tcphdr);
		break;
	}

	nf_route(nft_net(pkt), &dst, &fl, false, nft_pf(pkt));
	if (dst) {
		mtu = min(mtu, dst_mtu(dst));
		dst_release(dst);
	}

	if (mtu <= minlen || mtu > 0xffff)
		return TCP_MSS_DEFAULT;

	return mtu - minlen;
}