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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_dest {scalar_t__ tun_type; } ;
struct gre_base_hdr {int flags; scalar_t__ protocol; } ;
typedef  int /*<<< orphan*/  _greh ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int GRE_CSUM ; 
 int /*<<< orphan*/  IPPROTO_IPIP ; 
 scalar_t__ IP_VS_CONN_F_TUNNEL_TYPE_GRE ; 
 int gre_calc_hlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_flags_to_tnl_flags (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ip_vs_dest* ip_vs_find_tunnel (struct netns_ipvs*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ) ; 
 struct gre_base_hdr* skb_header_pointer (struct sk_buff*,unsigned int,int,struct gre_base_hdr*) ; 

__attribute__((used)) static int ipvs_gre_decap(struct netns_ipvs *ipvs, struct sk_buff *skb,
			  unsigned int offset, __u16 af,
			  const union nf_inet_addr *daddr, __u8 *proto)
{
	struct gre_base_hdr _greh, *greh;
	struct ip_vs_dest *dest;

	greh = skb_header_pointer(skb, offset, sizeof(_greh), &_greh);
	if (!greh)
		goto unk;
	dest = ip_vs_find_tunnel(ipvs, af, daddr, 0);
	if (!dest)
		goto unk;
	if (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) {
		__be16 type;

		/* Only support version 0 and C (csum) */
		if ((greh->flags & ~GRE_CSUM) != 0)
			goto unk;
		type = greh->protocol;
		/* Later we can support also IPPROTO_IPV6 */
		if (type != htons(ETH_P_IP))
			goto unk;
		*proto = IPPROTO_IPIP;
		return gre_calc_hlen(gre_flags_to_tnl_flags(greh->flags));
	}

unk:
	return 0;
}