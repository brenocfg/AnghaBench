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
struct nlattr {int dummy; } ;
struct TYPE_2__ {int version; int ihl; void* frag_off; void* protocol; void* tos; void* ttl; void* daddr; void* saddr; } ;
struct ip_tunnel_parm {TYPE_1__ iph; void* link; } ;
typedef  void* __u32 ;

/* Variables and functions */
 size_t IFLA_IPTUN_COLLECT_METADATA ; 
 size_t IFLA_IPTUN_FWMARK ; 
 size_t IFLA_IPTUN_LINK ; 
 size_t IFLA_IPTUN_LOCAL ; 
 size_t IFLA_IPTUN_PMTUDISC ; 
 size_t IFLA_IPTUN_PROTO ; 
 size_t IFLA_IPTUN_REMOTE ; 
 size_t IFLA_IPTUN_TOS ; 
 size_t IFLA_IPTUN_TTL ; 
 void* IPPROTO_IPIP ; 
 int /*<<< orphan*/  IP_DF ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static void ipip_netlink_parms(struct nlattr *data[],
			       struct ip_tunnel_parm *parms, bool *collect_md,
			       __u32 *fwmark)
{
	memset(parms, 0, sizeof(*parms));

	parms->iph.version = 4;
	parms->iph.protocol = IPPROTO_IPIP;
	parms->iph.ihl = 5;
	*collect_md = false;

	if (!data)
		return;

	if (data[IFLA_IPTUN_LINK])
		parms->link = nla_get_u32(data[IFLA_IPTUN_LINK]);

	if (data[IFLA_IPTUN_LOCAL])
		parms->iph.saddr = nla_get_in_addr(data[IFLA_IPTUN_LOCAL]);

	if (data[IFLA_IPTUN_REMOTE])
		parms->iph.daddr = nla_get_in_addr(data[IFLA_IPTUN_REMOTE]);

	if (data[IFLA_IPTUN_TTL]) {
		parms->iph.ttl = nla_get_u8(data[IFLA_IPTUN_TTL]);
		if (parms->iph.ttl)
			parms->iph.frag_off = htons(IP_DF);
	}

	if (data[IFLA_IPTUN_TOS])
		parms->iph.tos = nla_get_u8(data[IFLA_IPTUN_TOS]);

	if (data[IFLA_IPTUN_PROTO])
		parms->iph.protocol = nla_get_u8(data[IFLA_IPTUN_PROTO]);

	if (!data[IFLA_IPTUN_PMTUDISC] || nla_get_u8(data[IFLA_IPTUN_PMTUDISC]))
		parms->iph.frag_off = htons(IP_DF);

	if (data[IFLA_IPTUN_COLLECT_METADATA])
		*collect_md = true;

	if (data[IFLA_IPTUN_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_IPTUN_FWMARK]);
}